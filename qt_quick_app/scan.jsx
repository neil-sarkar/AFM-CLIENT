define(["react", "jsx!pages/heatmap_canvas", "jsx!pages/line_profile", "jsx!pages/inline_scan_controls", "jsx!pages/number_input", "jsx!pages/dropdown", "jsx!pages/text_input", "jsx!pages/save_folder"], function(React, HeatmapCanvas, LineProfile, InlineScanControls, NumberInput, Dropdown, TextInput, SaveFolderPicker) {
    function two_d_matrix_generator(rows, cols) {
        var matrix = new Array();
        for(var i=0; i < rows; i++) {
            matrix.push([]);
            for (var j = 0; j < cols; j++) {
                matrix[i].push("-1"); // TODO: put as constatn
            }
        }
        return matrix;
    }

    function one_d_matrix_generator(cols) {
        matrix = [];
        for (var i = 0; i < cols; i++)
            matrix.push("-1");
        return matrix;
    }

    function DataContainer(num_rows, num_columns) {
        this.num_rows = num_rows;
        this.num_columns = num_columns;
        this.heatmap = two_d_matrix_generator(num_rows, num_columns);
        this.profile = two_d_matrix_generator(num_rows, num_columns);
        
        // Used for cleaning and heatmap color mapping
        this.sum = 0;
        this.num_points = 0;
        this.sum_of_squares = 0;
        this.min = Number.POSITIVE_INFINITY;
        this.max = Number.NEGATIVE_INFINITY;
    }

    DataContainer.prototype.most_recent_line_profile = function() {
        for (var i = this.profile.length - 1; i >= 0; i--) // iterate backwards, since we assume we fill in one direction only
            if (this.profile[i][0] !== "-1") {// check if this row has been filled (assumes the entire row would be filled at once, therefore only check index 0 and assume the rest of the row is also -1)
                return this.profile[i].slice(); // must slice, otherwise the first row gets set to the last row retreived (I think it's because we pass by arrays reference and highcharts will retain a reference to the first points it gets, which means it can also set that data)
            }
    };
    
    function ScanView(name, data_source) {
        this.name = name;
        this.data_source = data_source;
        this.forward_data = null;
        this.reverse_data = null;
    }

    ScanView.prototype.init_data = function (num_rows, num_columns) {
        this.forward_data = new DataContainer(num_rows, num_columns);
        this.reverse_data = new DataContainer(num_rows, num_columns);
    };

    var scan_views = [];
    scan_views.push(new ScanView("Offset", scanner.new_offset_data));
    scan_views.push(new ScanView("Phase", scanner.new_phase_data));
    scan_views.push(new ScanView("Error", scanner.new_error_data));

    picture_map = [];
    picture_map.push({data_source: scanner.new_forward_offset_data, dom_id: "fo_image"});
    picture_map.push({data_source: scanner.new_forward_error_data, dom_id: "fe_image"});
    picture_map.push({data_source: scanner.new_forward_phase_data, dom_id: "fp_image"});
    picture_map.push({data_source: scanner.new_reverse_offset_data, dom_id: "ro_image"});
    picture_map.push({data_source: scanner.new_reverse_error_data, dom_id: "re_image"});
    picture_map.push({data_source: scanner.new_reverse_phase_data, dom_id: "rp_image"});


    var Scan = React.createClass({
        getInitialState: function() {
            return {
                scanning: false,
                starting_fresh_scan: true,
                current_view: 0,
                num_rows: 16,
                num_columns: 16,
                advanced: false,
            };
        },
        componentWillReceiveProps : function(nextProps) {
            if (nextProps.showStep === false) {
                $('#scan-wrapper').hide();
            } else {
                $('#scan-wrapper').show();
            }
        },
        pause_scanning: function() {
            this.setState({
                scanning: false,
            }, function(){
                scanner.pause_state_machine();
            });
        },
        set_scan_complete: function() {
            this.setState({
                scanning: false,
                starting_fresh_scan: true,
            });
        },
        componentDidMount: function() {

            scanner.num_rows_changed.connect(this.change_num_rows);
            scanner.num_columns_changed.connect(this.change_num_columns);
            scanner.all_data_received.connect(this.set_scan_complete);

            // connect scan views to their data sources
            for (var i = 0; i < picture_map.length; i++) {
                var bound_method = this.render_png.bind(this, picture_map[i].dom_id);
                picture_map[i].data_source.connect(bound_method);
            }
            // put blue marker on the first button
            $('.view-selector-button').first().addClass('selected-scan-view');
            $('.scan-image').hide();
            $('.scan-image').first().show();
        },
        render_png: function(dom_id, new_data) {
            document.getElementById(dom_id).src = "data:image/jpg;base64," + new_data;
        },
        change_num_rows: function (num_rows) {
            this.setState({
                num_rows: num_rows,
            });
        },
        change_num_columns: function (num_cols) {
            this.setState({
                num_columns: num_cols,
            });
        },
        tally_new_data: function(obj, x, y, z) {
            obj.profile[y][x] = z;
            obj.sum += z;
            obj.sum_of_squares += Math.pow(z, 2);
            obj.num_points += 1;
        },
        prepare_new_data: function (view_index, data) {
            // Data comes as (x,y,z.. max,min) * 2 for forward and reverse
            for (var i = 0; i < (data.length / 2) - 2; i += 3) {
                this.tally_new_data(scan_views[view_index].forward_data, data[i], data[i+1], data[i+2]);
                var j = data.length / 2 + i;
                this.tally_new_data(scan_views[view_index].reverse_data, data[j], data[j+1], data[j+2]);
            }

            // set the max and min for the whole scan - take the max of the new data's max current max so far
            scan_views[view_index].forward_data.max = Math.max(data[data.length/2 - 2], scan_views[view_index].forward_data.max);
            scan_views[view_index].forward_data.min = Math.min(data[data.length/2 - 1], scan_views[view_index].forward_data.min);
            scan_views[view_index].reverse_data.max = Math.max(data[data.length - 2], scan_views[view_index].reverse_data.max);
            scan_views[view_index].reverse_data.min = Math.min(data[data.length - 1], scan_views[view_index].reverse_data.min);
            
            // If the data we just got refers to what we're looking at currently, send the data to the heatmap
            if (Math.floor(this.state.current_view / 2) == view_index) {
                this.push_data_to_view(scan_views[view_index], false);
            }
        },
        push_data_to_view: function(scan_view, is_switching_views) {
            if (this.state.current_view % 2 === 0) { // we're looking at the forward 
                // this.refs.heatmap.receive_data(scan_view.forward_data.heatmap, scan_view.forward_data.min, scan_view.forward_data.max, scan_view.forward_data.num_points, is_switching_views);
            } else { // we;re looking at the reverse
                // this.refs.heatmap.receive_data(scan_view.reverse_data.heatmap, scan_view.reverse_data.min, scan_view.reverse_data.max, scan_view.forward_data.num_points, is_switching_views);
            }
            this.refs.line_profile.set_data(scan_view.forward_data.most_recent_line_profile(), scan_view.reverse_data.most_recent_line_profile());
        },
        // TODO: this whole tristate scanning button really should just be done with a dictionary
        start_or_resume_scanning: function() {
            this.setState({
                num_rows: scanner.num_rows(),
                num_columns: scanner.num_columns(),
            });
            this.setState({
                scanning: true,
            }, function(){
                if (this.state.starting_fresh_scan) {
                    scanner.start_state_machine();
                } else {
                    scanner.resume_state_machine();
                }
                this.refs.line_profile.clear_plotlines();
                this.setState({
                    starting_fresh_scan: false
                });
            });
        },
        clear_scan: function() {
            this.pause_scanning();
            scanner.reset();
            $(".scan-image").each(function(i) {
                $('.scan-image').eq(i).src = ""; // Delete the images
            });
            setTimeout(function() {
                for (var i = 0; i < scan_views.length; i++) {
                    scan_views[i].init_data(this.state.num_rows, this.state.num_columns);
                }
                this.refs.line_profile.erase_data();
                this.set_scan_complete();
            }.bind(this), 200); // give time for the scnaner to actually pause 
            // so data doesn't get rendered 
            // (maybe this should happen on a signal) or have a "accepting data" state check before dispatching
        },
        eliminate_outliers: function() {
            current_data_container = this.state.current_view % 2 === 0 ? scan_views[Math.floor(this.state.current_view / 2)].forward_data : scan_views[Math.floor(this.state.current_view / 2)].reverse_data;
            current_heatmap = current_data_container.heatmap;
            var rms = Math.sqrt(current_data_container.sum_of_squares / current_data_container.num_points);
            var mean = current_data_container.sum / current_data_container.num_points;
            var rms_multiplier = scanner.rms_threshold();
            var min = Math.max(mean - rms_multiplier * rms, current_data_container.min);
            var max = Math.min(mean + rms_multiplier * rms, current_data_container.max);
            // this.refs.heatmap.eliminate_outliers(current_heatmap, min, max);
            this.refs.line_profile.draw_outlier_plotlines(min, max);
        },
        handle_view_selector_click: function(dom_id_of_image, e) {
            // Set style of selected name
            var target = $(e.target);
            $('.view-selector-button').removeClass('selected-scan-view');
             // for some reason the click events sometimes register under the p tag, sometimes under the span
            if (target.is('p')) {
                target.addClass('selected-scan-view');
            } else if (target.is('span')) {
                target.parent().addClass("selected-scan-view");
            }

            $(".scan-image").hide();
            $("#" + dom_id_of_image).show();
        },
        get_specific_row_profile: function(data, y_value) {
            return data.slice(y_value * this.state.num_columns, (y_value + 1) * this.state.num_columns);
        },
        dummy_data: function (argument) {
            // this.refs.heatmap.dummy_data();
        },
        handle_heatmap_click: function(x, y) {
            var current_data_set = scan_views[Math.floor(this.state.current_view / 2)];
            this.refs.line_profile.set_data(current_data_set.forward_data.profile[y], current_data_set.reverse_data.profile[y]);
        },
        toggle_advanced_controls: function () {
            this.setState({
                advanced: !this.state.advanced
            });
        },
        save_data: function () {
            afm.save_scan_data();
        },
        render: function() {
             // the states will need fixing - clean button should be disabled until scanning completely done (should edit how states work)   
            return (
                <div className="wrapper" id="scan-wrapper">
                    <div className="left-flexbox">
                        <div className="top-row scan-top">
                            <div className="scan-view-selector-container">
                                <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "fo_image")}> Forward Offset</p>
                                <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "ro_image")}> Reverse Offset</p>
                                <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "fp_image")}> Forward Phase</p>
                                <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "rp_image")}> Reverse Phase</p>
                                <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "fe_image")}> Foward Error</p>
                                <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "re_image")}> Reverse Error</p>
                            </div>
                            <img src="" id="fo_image" className="scan-image" />
                            <img src="" id="ro_image" className="scan-image" />
                            <img src="" id="fp_image" className="scan-image" />
                            <img src="" id="rp_image" className="scan-image" />
                            <img src="" id="fe_image" className="scan-image" />
                            <img src="" id="re_image" className="scan-image" />
                        </div>
                        <LineProfile ref="line_profile" chart_name={this.props.name}/>
                    </div>
                    <div className="right-flexbox">
                        <div className="step-name">Scan</div>
                        <div className="step-description">
                            Press "Scan" to begin imaging.
                        </div>
                        <div>
                            <Dropdown options_list={[
                                        {text: "8", cmd_number: 8},
                                        {text: "16", cmd_number: 16},
                                        {text: "32", cmd_number: 32},
                                        {text: "64", cmd_number: 64},
                                        {text: "128", cmd_number: 128},
                                        {text: "256", cmd_number: 256},
                                        {text: "512", cmd_number: 512},
                                        {text: "1024", cmd_number: 1024},
                                    ]}
                                    selection_method={scanner.set_num_columns}
                                    notify_signal={scanner.num_columns_changed}
                                    title="Number of pixels per line"/>
                            <Dropdown options_list={[
                                        {text: "8", cmd_number: 8},
                                        {text: "16", cmd_number: 16},
                                        {text: "32", cmd_number: 32},
                                        {text: "64", cmd_number: 64},
                                        {text: "128", cmd_number: 128},
                                        {text: "256", cmd_number: 256},
                                        {text: "512", cmd_number: 512},
                                        {text: "1024", cmd_number: 1024},
                                    ]}
                                    selection_method={scanner.set_num_rows}
                                    notify_signal={scanner.num_rows_changed}
                                    title="Number of lines"/>
                            <NumberInput value_type="scan"
                                        name="Number of averages taken at each point"
                                        min={0}
                                        max={255} 
                                        step={1} 
                                        notify_signal={scanner.num_averages_changed} 
                                        get_value={scanner.num_averages} 
                                        set_value={scanner.set_num_averages} />
                            <NumberInput value_type="scan" 
                                        name="Time spent at each point (ms)"
                                        min={0}
                                        max={255}
                                        step={1} 
                                        notify_signal={scanner.dwell_time_changed} 
                                        get_value={scanner.dwell_time} 
                                        set_value={scanner.set_dwell_time} />
                            <TextInput name="File name base" 
                                        notify_signal={scanner.base_file_name_changed}
                                        get_value={scanner.base_file_name}
                                        set_value={scanner.set_base_file_name} />
                            <SaveFolderPicker compressed={true}/>
                        </div>
                        <div className="top-row">
                            <button className="action-button" onClick={this.state.scanning ? this.pause_scanning : this.start_or_resume_scanning}>{this.state.scanning ? "Pause" : (this.state.starting_fresh_scan ? "Scan" : "Resume")}</button>
                            <button className="action-button" onClick={this.clear_scan}>Reset</button>
                            <button className="action-button" onClick={this.save_data} disabled={this.state.scanning}>Save</button>
                        </div>
                        <div className="nav-buttons-wrapper">
                            <button className="action-button" id="back-button" onClick={this.props.go_to_previous_step}>Back</button>
                        </div>
                        <p className="advanced-controls-toggle" onClick={this.toggle_advanced_controls}><span>{this.state.advanced ? "Hide" : "Show"}</span> Advanced Controls</p>
                        <div className={(this.state.advanced ? "visible" : "hidden") + " " + "top-row"}>
                            <InlineScanControls />
                            <button className="action-button" onClick={this.eliminate_outliers} disabled={this.state.scanning}>Clean</button>
                        </div>
                    </div>
                </div>
                )
        },
    });
    return Scan;
});
