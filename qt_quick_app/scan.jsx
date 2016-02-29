define(["react", "jsx!pages/scan_heatmap", "jsx!pages/line_profile", "jsx!pages/inline_scan_controls"], function(React, ScanHeatMap, LineProfile, InlineScanControls) {
    var scan_views = [
        {
            name: "Foward Offset",
            uid: 0,
            direction: "forward",
            data_couple: 1,
            data_source: scanner.new_forward_offset_data,
            data: [],
            line_profile_data: [],
            sum: 0,
            num_points: 0,
            sum_of_squares: 0,
        },
        {
            name: "Reverse Offset",
            uid: 1,
            direction: "reverse",
            data_couple: 0,
            data_source: scanner.new_reverse_offset_data,
            data: [],
            line_profile_data: [],
            sum: 0,
            num_points: 0,
            sum_of_squares: 0,
        },
        {
            name: "Foward Phase",
            uid: 2,
            direction: "forward",
            data_couple: 3,
            data_source: scanner.new_forward_phase_data,
            data: [],
            line_profile_data: [],
            sum: 0,
            num_points: 0,
            sum_of_squares: 0,
        },
        {
            name: "Reverse Phase",
            uid: 3,
            direction: "reverse",
            data_couple: 2,
            data_source: scanner.new_reverse_phase_data,
            data: [],
            line_profile_data: [],
            sum: 0,
            num_points: 0,
            sum_of_squares: 0,
        },
        {
            name: "Foward Error",
            uid: 4,
            direction: "forward",
            data_couple: 5,
            data_source: scanner.new_forward_error_data,
            data: [],
            line_profile_data: [],
            sum: 0,
            num_points: 0,
            sum_of_squares: 0,
        },
        {
            name: "Reverse Error",
            uid: 5,
            direction: "reverse",
            data_couple: 4,
            data_source: scanner.new_reverse_error_data,
            data: [],
            line_profile_data: [],
            sum: 0,
            num_points: 0,
            sum_of_squares: 0,
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
        prepare_new_data: function (view_index, data) {
            for (var i = 0; i < data.length; i += 3) {
                scan_views[view_index].data.push({x: data[i], y: data[i+1], value: data[i+2]});
                scan_views[view_index].line_profile_data.push({x: data[i], y: data[i+2]});
                scan_views[view_index].sum += data[i + 2];
                scan_views[view_index].sum_of_squares += Math.pow(data[i + 2], 2);
                scan_views[view_index].num_points += 1;
            }
            if (this.state.current_view == view_index) {
                this.push_most_recent_data_to_view(scan_views[view_index].data, scan_views[view_index].line_profile_data);
            }
        },
        push_most_recent_data_to_view: function(heatmap_data, line_profile_data) {
            this.refs.heatmap.set_data(heatmap_data);
            this.refs.line_profile.set_data(line_profile_data.slice(Math.max(line_profile_data.length - this.state.send_back_count, 0)));
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
        clear_scan: function() {
            this.pause_scanning();
            scanner.reset();
            this.push_most_recent_data_to_view([], []);
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
                this.push_most_recent_data_to_view([], []);
                this.push_most_recent_data_to_view(scan_views[index].data, scan_views[index].line_profile_data);
            });
        },
        handle_tooltip_select: function(y_value) {
            this.refs.line_profile.set_data(scan_views[this.state.current_view].line_profile_data.slice(y_value * this.state.num_columns, (y_value + 1) * this.state.num_columns));
        },
        render: function() {
             // the states will need fixing - clean button should be disabled until scanning completely done (should edit how states work)   
            return (
                <div className="wrapper" id="scan-wrapper">
                    <div className="left-flexbox">
                        <div className="top-row">
                            <div className="scan-view-selector-container">
                                {scan_views.map(function(view, i) {
                                var boundClick = this.handle_view_selector_click.bind(this, i);
                                return (
                                    <p className="view-selector-button" onClick={boundClick}>{view.name}</p>
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