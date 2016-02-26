define(["react", "dom", "heatmap", "jsx!pages/line_profile", "jsx!pages/scan_heatmap"], function(React, ReactDOM, heatmap, LineProfile, ScanHeatMap) {
    var ScanViewer = React.createClass({
        getInitialState: function() {
            return {
                sum: 0, // sum of all data being plotted
                num_points: 0, // total number of points plotted
                sum_of_squares: 0,
                visible: false,
                buffer: []
                // together, we find the average
            };
        },
        componentDidMount: function() {
            this.props.data_source.connect(this.handle_new_data_wrapper);
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
        },
        set_visible:function(bool) {
            var that = this;
            this.setState({
                visible: bool
            }, function() {
                if (bool) {
                    var num_data_per_line = 128 * 3;
                    var num_lines = this.state.buffer.length / num_data_per_line;
                    console.log(that.state.buffer);
                    for (var j = 0; j < num_lines; j++) {
                        setTimeout(function() {
                            var offset = j * num_lines;
                            for (var i = 0; i < num_data_per_line; i += 3) {
                                var x = that.state.buffer[i + offset];
                                var y = that.state.buffer[i+1 + offset];
                                var z = that.state.buffer[i+2 + offset];
                                that.dispatch_data(x, y, z, (i === 0));
                            }
                            that.prompt_redraw();
                        }, j*10);
                    }
                    
                    // this.setState({
                    //     buffer: []
                    // });
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
            var style = {};
            if (this.state.visible)
                style = {display: "block"};
            else
                style= {display: "none"};

            return (
                <div className="scan-viewer" id={this.props.dom_id} style={style}>
                    <ScanHeatMap ref="heatmap" chart_name={this.props.name} handle_tooltip_select={this.handle_tooltip_select} />
                    <LineProfile ref="line_profile" chart_name={this.props.name}/>
                </div>
            );
        }
    });
    return ScanViewer;
});