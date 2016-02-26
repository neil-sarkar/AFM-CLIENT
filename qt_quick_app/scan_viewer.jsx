define(["react", "dom", "heatmap", "jsx!pages/line_profile", "jsx!pages/scan_heatmap"], function(React, ReactDOM, heatmap, LineProfile, ScanHeatMap) {
    var ScanViewer = React.createClass({
        getInitialState: function() {
            return {
                sum: 0, // sum of all data being plotted
                num_points: 0, // total number of points plotted
                sum_of_squares: 0,
                num_lines: 0,
                visible: true,
                buffer: [],
                fwd_offset: [],
                rev_offset: [],
                fwd_amplitude: [],
                rev_amplitude: [],
            };
        },
        componentDidMount: function() {
            // this.props.data_source.connect(this.handle_new_data_wrapper);
            scanner.new_forward_offset_data.connect(this.add_fwd_data);
            scanner.new_reverse_offset_data.connect(this.add_rev_data);
            scanner.new_forward_offset_data.connect(this.add_fwd_amp_data);
            scanner.new_reverse_offset_data.connect(this.add_rev_amp_data);
        },
        add_fwd_data: function(data) {
            console.log("called");
            prepared_data = [];
            for (var i = 0; i < data.length; i += 3)
                prepared_data.push({x: data[i], y: data[i+1], value: data[i+2]});

            this.setState({
                fwd_offset: this.state.fwd_offset.concat(prepared_data)
            }, function() {
                console.log(this.state.view, this.state.fwd_offset.length);
                if (this.state.view === 0)
                    this.refs.heatmap.set_data(this.state.fwd_offset); // maybe put these on separate series?
            });
        },
        add_rev_data: function(data) {
            prepared_data = [];
            for (var i = 0; i < data.length; i += 3)
                prepared_data.push({x: data[i], y: data[i+1], value: data[i+2]});

            this.setState({
                rev_offset: this.state.rev_offset.concat(prepared_data)
            }, function() {
                if (this.state.view == 1)
                    this.refs.heatmap.set_data(this.state.rev_offset);
            });
        },
        add_fwd_amp_data: function(data) {
            prepared_data = [];
            for (var i = 0; i < data.length; i += 3)
                prepared_data.push({x: data[i], y: data[i+1], value: data[i+2]});

            this.setState({
                fwd_amplitude: this.state.fwd_amplitude.concat(prepared_data)
            }, function() {
                if (this.state.view === 2)
                    this.refs.heatmap.set_data(this.state.fwd_amplitude); // maybe put these on separate series?
            });
        },
        add_rev_amp_data: function(data) {
            prepared_data = [];
            for (var i = 0; i < data.length; i += 3)
                prepared_data.push({x: data[i], y: data[i+1], value: data[i+2]});

            this.setState({
                rev_amplitude: this.state.rev_amplitude.concat(prepared_data)
            }, function() {
                if (this.state.view == 3)
                    this.refs.heatmap.set_data(this.state.rev_amplitude);
            });
        },
        switch_view: function(i) {
            if (this.state.view != i) {
                this.setState({
                    view: i
                });
                this.refs.heatmap.set_data([]);
                if (i === 0)
                    this.refs.heatmap.set_data(this.state.fwd_offset);
                else if (i == 1)
                    this.refs.heatmap.set_data(this.state.rev_offset);
                else if (i == 2)
                    this.refs.heatmap.set_data(this.state.fwd_amplitude);
                else if (i == 3)
                    this.refs.heatmap.set_data(this.state.rev_amplitude);
            }
        },
        handle_new_data_wrapper: function(data) {
            var self = this;
            setTimeout(function(){ self.handle_new_data(data); }, 0);
        },
        handle_new_data: function(data) {
            var self = this;
            if (this.state.visible === true) {
                for (var i = 0; i < data.length; i += 3) {
                    self.dispatch_data(data[i], data[i+1], data[i+2], (i === 0));
                }
                this.prompt_redraw();
            } else {
                this.setState({
                    buffer: this.state.buffer.concat(data)
                });
            }
            if (this.state.num_lines % 6 == this.props.order_num && !this.state.visible) {
                this.process_buffer();
            }

            this.setState({
                num_lines: this.state.num_lines + 1
            });
        },
        process_buffer : function() {
            for (var i = 0; i < this.state.buffer.length; i += 3) {
                var x = this.state.buffer[i];
                var y = this.state.buffer[i+1];
                var z = this.state.buffer[i+2];
                this.dispatch_data(x, y, z, (i % (128 * 3) === 0));
            }
            this.setState({
                buffer: []
            });
        },
        set_visible:function(bool) {
            var that = this;
            this.setState({
                visible: bool
            }, function() {
                if (bool) {
                    that.process_buffer();
                }
            });
        },
        dispatch_data: function(x, y, z, new_series) {
            var self = this;
            setTimeout(function() {
                if (new_series)
                    self.refs.line_profile.addSeries();
                self.refs.heatmap.asyncAddPoint(x, y, z);
            }, 0);
            setTimeout(function() {
                self.refs.line_profile.asyncAddPoint(x, z);
            }, 0);
        },
        prompt_redraw: function() {
            var self = this;
            setTimeout(function() {
                self.refs.heatmap.redraw();
            }, 0);
            setTimeout(function() {
                self.refs.line_profile.redraw();
            }, 0);
        },
        handle_tooltip_select: function(series_index) {
            this.refs.line_profile.select_series_to_display(series_index);
        },
        clear: function() {
            this.refs.heatmap.erase_data();
            this.refs.line_profile.erase_data();
            this.setState({
                sum: 0,
                num_points: 0,
                sum_of_squares: 0
            });
        },
        hide: function() {
            $('#' + this.props.dom_id).hide();
        },
        show: function() {
            $('#' + this.props.dom_id).show();
        },
        eliminate_outliers: function() {
            if (this.state.num_points === 0)
                return;
            var rms = Math.sqrt(this.state.sum_of_squares / this.state.num_points);
            var mean = this.state.sum / this.state.num_points;
            var rms_multiplier = scanner.rms_threshold();
            var min = mean - rms_multiplier * rms;
            var max = mean + rms_multiplier * rms;
            this.refs.heatmap.eliminate_outliers(min, max);
            this.refs.line_profile.draw_outlier_plotlines(min, max);
        },
        render: function() {
            return (
                <div className="scan-viewer" id={this.props.dom_id}>
                    <ScanHeatMap ref="heatmap" chart_name={this.props.name} handle_tooltip_select={this.handle_tooltip_select} />
                    <LineProfile ref="line_profile" chart_name={this.props.name}/>
                </div>
            );
        }
    });
    return ScanViewer;
});