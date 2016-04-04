define(["react", "jsx!pages/heatmap_canvas", "jsx!pages/line_profile", "jsx!pages/inline_scan_controls"], function(React, HeatmapCanvas, LineProfile, InlineScanControls) {
    function two_d_matrix_generator(rows, cols) {
        var matrix = new Array();
        for(var i=0; i<rows; i++) {
            matrix.push([]);
            for (var j = 0; j < cols; j++) {
                matrix[i].push("-1");
            }
        }
        return matrix;
    }

    function one_d_matrix_generator(cols) {
        return new Array(cols);
    }

    function DataContainer(num_rows, num_columns) {
        this.num_rows = num_rows;
        this.num_columns = num_columns;
        this.heatmap = two_d_matrix_generator(num_rows, num_columns);
        this.profile = one_d_matrix_generator(num_columns);
        this.latest_diff = [];
        this.sum = 0;
        this.num_points = 0;
        this.sum_of_squares = 0;
        this.min = Number.POSITIVE_INFINITY;
        this.max = Number.NEGATIVE_INFINITY;
    }
    
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

    var Scan = React.createClass({
        getInitialState: function() {
            return {
                scanning: false,
                starting_fresh_scan: true,
                current_view: 0,
                current_line: 0,
                num_rows: 10,
                num_columns: 10,
                send_back_count: 0
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
            for (var i = 0; i < scan_views.length; i++) {
                var bound_method = this.prepare_new_data.bind(this, i);
                scan_views[i].data_source.connect(bound_method);
            }
            $('.view-selector-button').first().addClass('selected-scan-view');
        },
        change_num_rows: function (num_rows) {
            this.setState({
                num_rows: num_rows,
            }, function() {
                this.refs.heatmap.change_pixel_size(this.state.num_rows, this.state.num_columns);
            });
        },
        change_num_columns: function (num_cols) {
            this.setState({
                num_columns: num_cols,
            }, function() {
                this.refs.heatmap.change_pixel_size(this.state.num_rows, this.state.num_columns);
            });
        },
        tally_new_data: function(obj, x, y, z) {
            obj.heatmap[x][y] = z;
            obj.profile[x] = z;
            obj.sum += z;
            obj.sum_of_squares += Math.pow(z, 2);
            obj.num_points += 1;
        },
        prepare_new_data: function (view_index, data) {
            // console.log("New da", data);
            // console.log("Heatmap before adding", scan_views[view_index].forward_data.heatmap);
            // console.log("Heatmap before adding", this.refs.heatmap.state.data);
            for (var i = 0; i < (data.length / 2) - 2; i += 3) {
                // console.log(data[i], data[i+1], data[i+2]);
                this.tally_new_data(scan_views[view_index].forward_data, data[i], data[i+1], data[i+2]);
                var j = data.length / 2 + i;
                this.tally_new_data(scan_views[view_index].reverse_data, data[j], data[j+1], data[j+2]);
            }
            // console.log("Heatmap after adding", scan_views[view_index].forward_data.heatmap);
            scan_views[view_index].forward_data.max = Math.max(data[data.length/2 - 2], scan_views[view_index].forward_data.max);
            scan_views[view_index].forward_data.min = Math.min(data[data.length/2 - 1], scan_views[view_index].forward_data.min);
            scan_views[view_index].reverse_data.max = Math.max(data[data.length - 2], scan_views[view_index].reverse_data.max);
            scan_views[view_index].reverse_data.min = Math.min(data[data.length - 1], scan_views[view_index].reverse_data.min);
            if (Math.floor(this.state.current_view / 2) == view_index) {
                this.push_data_to_view(scan_views[view_index], false);
            }
        },
        limit_line_profile_data: function(data) {
            return data.slice(Math.max(data.length - this.state.send_back_count, 0));
        },
        push_data_to_view: function(data_obj, is_switching_views) {
            if (this.state.current_view % 2 === 0) {
                // console.log("heatmap send", data_obj.forward_data.heatmap);
                this.refs.heatmap.receive_data(data_obj.forward_data.heatmap, data_obj.forward_data.min, data_obj.forward_data.max, data_obj.forward_data.num_points, is_switching_views);
            } else {
                this.refs.heatmap.receive_data(data_obj.reverse_data.heatmap, data_obj.reverse_data.min, data_obj.reverse_data.max, data_obj.forward_data.num_points, is_switching_views);
            }
            // this.refs.line_profile.set_data(this.limit_line_profile_data(data_obj.forward_data.profile), this.limit_line_profile_data(data_obj.reverse_data.profile));
        },
        // TODO: this whole tristate scanning button really should just be done with a dictionary
        start_or_resume_scanning: function() {
            this.setState({
                num_rows: scanner.num_rows(),
                num_columns: scanner.num_columns(),
                send_back_count: scanner.send_back_count()
            });
            this.setState({
                scanning: true,
            }, function(){
                if (this.state.starting_fresh_scan) {
                    for (var i = 0; i < scan_views.length; i++) {
                        scan_views[i].init_data(this.state.num_rows, this.state.num_columns);
                        this.refs.heatmap.change_pixel_size(this.state.num_rows, this.state.num_columns);
                    }
                    scanner.start_state_machine();
                } else {
                    scanner.resume_state_machine();
                }
                // TODO: decide if it's worth repushing the data to the heatmap - otherwise it will remain "cleaned" if the user pressed clean
                // until such a time that a full rerender is necessary
                this.refs.line_profile.clear_plotlines();
                this.setState({
                    starting_fresh_scan: false
                });
            });
        },
        clear_scan: function() {
            this.pause_scanning();
            scanner.reset();
            setTimeout(function() {
                for (var i = 0; i < scan_views.length; i++) {
                    scan_views[i].init_data(this.state.num_rows, this.state.num_columns);
                }
                this.refs.line_profile.erase_data();
                this.refs.heatmap.erase_data();
                this.set_scan_complete();
            }.bind(this), 200); // give time for the scnaner to actually pause 
            // so data doesn't get rendered 
            // (maybe this should happen on a signal) or have a "accepting data" state check before dispatching
        },
        eliminate_outliers: function() {
            current_view_obj = this.state.current_view % 2 === 0 ? scan_views[Math.floor(this.state.current_view / 2)].forward_data : scan_views[Math.floor(this.state.current_view / 2)].reverse_data;
            var current_data = current_view_obj.heatmap;
            var rms = Math.sqrt(current_view_obj.sum_of_squares / current_view_obj.num_points);
            var mean = current_view_obj.sum / current_view_obj.num_points;
            var rms_multiplier = scanner.rms_threshold();
            var min = mean - rms_multiplier * rms;
            var max = mean + rms_multiplier * rms;
            this.refs.heatmap.eliminate_outliers(min, max);
            this.refs.line_profile.draw_outlier_plotlines(min, max);
        },
        handle_view_selector_click: function(index, e) {
            // Set style of selected name
            var target = $(e.target);
            $('.view-selector-button').removeClass('selected-scan-view');
             // for some reason the click events sometimes register under the p tag, sometimes under the span
            if (target.is('p')) {
                target.addClass('selected-scan-view');
            } else if (target.is('span')) {
                target.parent().addClass("selected-scan-view");
            }

            this.setState({
                current_view: index
            }, function () {
                this.refs.line_profile.clear_plotlines();
                this.push_data_to_view(scan_views[Math.floor(index/2)], true);
            });
        },
        get_specific_row_profile: function(data, y_value) {
            return data.slice(y_value * this.state.num_columns, (y_value + 1) * this.state.num_columns);
        },
        handle_tooltip_select: function(y_value) {
            var current_data_set = scan_views[Math.floor(this.state.current_view / 2)];
            this.refs.line_profile.set_data(this.get_specific_row_profile(current_data_set.forward_data.profile, y_value), this.get_specific_row_profile(current_data_set.reverse_data.profile, y_value));
        },
        dummy_data: function (argument) {
            this.refs.heatmap.dummy_data();
        },
        render: function() {
             // the states will need fixing - clean button should be disabled until scanning completely done (should edit how states work)   
            return (
                <div className="wrapper" id="scan-wrapper">
                    <div className="left-flexbox">
                        <div className="top-row scan-top">
                            <div className="scan-view-selector-container">
                                {scan_views.map(function(view, i) {
                                    var forward_bound_click = this.handle_view_selector_click.bind(this, 2*i);
                                    var reverse_bound_click = this.handle_view_selector_click.bind(this, 2*i + 1);
                                    return (
                                        <div>
                                            <p className="view-selector-button" onClick={forward_bound_click} key={2*i}>Forward {view.name}</p>
                                            <p className="view-selector-button" onClick={reverse_bound_click} key={2*i + 1}>Reverse {view.name}</p>
                                        </div>
                                        );
                                }, this)}
                            </div>
                            <HeatmapCanvas ref="heatmap" id="heatmap1" />
                        </div>
                        <LineProfile ref="line_profile" chart_name={this.props.name}/>
                    </div>
                    <div className="right-flexbox">
                        <div className="step-name">Scan</div>
                        <div className="step-description">
                        Scanning is so cool.
                        </div>
                        <div className="top-row">
                            <button className="action-button" onClick={this.state.scanning ? this.pause_scanning : this.start_or_resume_scanning}>{this.state.scanning ? "Pause" : (this.state.starting_fresh_scan ? "Scan" : "Resume")}</button>
                            <button className="action-button" onClick={this.clear_scan}>Clear</button>
                            <button className="action-button" onClick={this.eliminate_outliers} disabled={this.state.scanning}>Clean</button>
                            <button className="action-button" onClick={afm.save_scan_data} disabled={this.state.scanning}>Download Data</button>
                            <button className="action-button" onClick={this.dummy_data} disabled={this.state.scanning}>Dummy</button>
                        </div>
                        <InlineScanControls />
                        <div className="nav-buttons-wrapper">
                            <button className="action-button" id="back-button" onClick={this.props.go_to_previous_step}>Back</button>
                        </div>
                    </div>
                </div>
                )
        },
    });
    return Scan;
});