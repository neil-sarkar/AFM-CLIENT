define(["react", "jsx!pages/scan_heatmap", "jsx!pages/line_profile", "jsx!pages/inline_scan_controls"], function(React, ScanHeatMap, LineProfile, InlineScanControls) {
    var null_view = {
            forward_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            },
            reverse_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            }
        }
    var scan_views = [
        {
            name: "Offset",
            data_source: scanner.new_offset_data,
            forward_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            },
            reverse_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            }
        },
        {
            name: "Phase",
            data_source: scanner.new_phase_data,
            forward_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            },
            reverse_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            }
        },
        {
            name: "Error",
            data_source: scanner.new_error_data,
            forward_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            },
            reverse_data: {
                heatmap: [],
                profile: [],
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            }
        },
    ];
    var Scan = React.createClass({
        getInitialState: function() {
            return {
                scanning: false,
                starting_fresh_scan: true,
                current_view: 0,
                current_line: 0,    
                num_rows: 0,
                num_columns: 0,
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
            scanner.all_data_received.connect(this.set_scan_complete);
            for (var i = 0; i < scan_views.length; i++) {
                var bound_method = this.prepare_new_data.bind(this, i);
                scan_views[i].data_source.connect(bound_method);
            }
        },
        tally_new_data: function(obj, x, y, z) {
            obj.heatmap.push({x: x, y: y, value: z});
            obj.profile.push({x: x, y: z});
            obj.sum += z;
            obj.sum_of_squares += Math.pow(z, 2);
            obj.num_points += 1;
        },
        prepare_new_data: function (view_index, data) {
            for (var i = 0; i < data.length / 2; i += 3) {
                this.tally_new_data(scan_views[view_index].forward_data, data[i], data[i+1], data[i+2]);
                var j = data.length / 2 + i;
                this.tally_new_data(scan_views[view_index].reverse_data, data[j], data[j+1], data[j+2]);
            }
            if (Math.floor(this.state.current_view / 2) == view_index) {
                this.push_data_to_view(scan_views[view_index]); 
            }
        },
        limit_line_profile_data: function(data) {
            return data.slice(Math.max(data.length - this.state.send_back_count, 0));
        },
        push_data_to_view: function(data_obj) {
            if (this.state.current_view % 2 == 0) {
                this.refs.heatmap.set_data(data_obj.forward_data.heatmap);    
            } else {
                this.refs.heatmap.set_data(data_obj.reverse_data.heatmap);
            }
            this.refs.line_profile.set_data(this.limit_line_profile_data(data_obj.forward_data.profile), this.limit_line_profile_data(data_obj.reverse_data.profile));
        },
        // this whole tristate scanning button really should just be done with a dictionary
        start_or_resume_scanning: function() {
            this.setState({
                num_rows: scanner.num_rows(),
                num_columns: scanner.num_columns(),
                send_back_count: scanner.send_back_count().charCodeAt() // js interprets the quint8 as a char
            });
            this.setState({
                scanning: true,
            }, function(){
                if (this.state.starting_fresh_scan) {
                    scanner.start_state_machine();
                } else {
                    scanner.resume_state_machine();
                }
                this.setState({
                    starting_fresh_scan: false
                });
            });
        },
        reset_data_buffers: function () {
            for (var i = 0; i < scan_views.length; i++) {
                scan_views[i].data = [];
                scan_views[i].line_profile_data = [];
            }
        },
        push_empty_view: function (argument) {
            this.push_data_to_view(null_view);
        },
        clear_scan: function() {
            this.pause_scanning();
            scanner.reset();
            this.push_empty_view();
            setTimeout(function() {
                for (var i = 0; i < scan_views.length; i++) {
                    scan_views[i].data = [];
                }
                this.refs.line_profile.erase_data();
                this.refs.heatmap.erase_data();
                this.set_scan_complete();
            }.bind(this), 100); // give time for the scnaner to actually pause 
            // so data doesn't get rendered 
            // (maybe this should happen on a signal) or have a "accepting data" state check before dispatching
            this.reset_data_buffers();
        },
        eliminate_outliers: function() {
            current_view_obj = scan_views[this.state.current_view];
            var current_data = current_view_obj.data;
            var rms = Math.sqrt(current_view_obj.sum_of_squares / current_view_obj.num_points);
            var mean = current_view_obj.sum / current_view_obj.num_points;
            var rms_multiplier = scanner.rms_threshold();
            var min = mean - rms_multiplier * rms;
            var max = mean + rms_multiplier * rms;
            this.refs.heatmap.eliminate_outliers(current_data, min, max);
            this.refs.line_profile.draw_outlier_plotlines(min, max);
        },
        handle_view_selector_click: function(index) {
            this.setState({
                current_view: index
            }, function () {
                this.refs.line_profile.clear_plotlines();
                this.push_empty_view();
                console.log(scan_views[Math.floor(index/2)]);
                this.push_data_to_view(scan_views[Math.floor(index/2)]);
            });
        },
        get_data_couple: function(index) {
            return scan_views[scan_views[index].data_couple]
        },
        handle_tooltip_select: function(y_value) {
            this.refs.line_profile.set_data(scan_views[this.state.current_view].line_profile_data.slice(y_value * this.state.num_columns, (y_value + 1) * this.state.num_columns), 
                this.get_data_couple(this.state.current_view).line_profile_data.slice(y_value * this.state.num_columns, (y_value + 1) * this.state.num_columns));
        },
        render: function() {
             // the states will need fixing - clean button should be disabled until scanning completely done (should edit how states work)   
            return (
                <div className="wrapper" id="scan-wrapper">
                    <div className="left-flexbox">
                        <div className="top-row">
                            <div className="scan-view-selector-container">
                                {scan_views.map(function(view, i) {
                                var forward_bound_click = this.handle_view_selector_click.bind(this, 2*i);
                                var reverse_bound_click = this.handle_view_selector_click.bind(this, 2*i + 1);
                                return (
                                    <div>
                                        <p className="view-selector-button" onClick={forward_bound_click}>Forward {view.name}</p>
                                        <p className="view-selector-button" onClick={reverse_bound_click}>Reverse {view.name}</p>
                                    </div>
                                    );
                                }, this)}
                            </div>
                            <ScanHeatMap ref="heatmap" chart_name={this.props.name} handle_tooltip_select={this.handle_tooltip_select} />
                        </div>
                        <LineProfile ref="line_profile" chart_name={this.props.name}/>
                    </div>
                    <div className="right-flexbox">
                        <div className="step-name">Scan</div>
                        <div className="step-description">
                        Scanning is so cool.
                        </div>
                        <button className="action-button" onClick={this.state.scanning ? this.pause_scanning : this.start_or_resume_scanning}>{this.state.scanning ? "Pause" : (this.state.starting_fresh_scan ? "Scan" : "Resume")}</button>
                        <button className="action-button" onClick={this.clear_scan}>Clear</button>
                        <button className="action-button" onClick={this.eliminate_outliers} disabled={this.state.scanning}>Clean</button>
                        <button className="action-button" onClick={scanner.save_raw_data} disabled={this.state.scanning}>Download Data</button>
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