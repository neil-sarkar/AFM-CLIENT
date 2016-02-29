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
            };
        },
        componentDidMount: function() {
        },
        receive_data: function(heatmap_data, line_profile_data) {
            this.refs.heatmap.set_data(heatmap_data);
            console.log(line_profile_data.length);
            this.refs.line_profile.set_data(line_profile_data);
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
        handle_tooltip_select: function(series_index) {
            this.refs.line_profile.select_series_to_display(series_index);
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
                <div className="scan-viewer">
                    <div>
                        <div className="scan-view-selector-container">
                            {["scan_views", "lol"].map(function(view, i) {
                            // var boundClick = this.handle_view_selector_click.bind(this, i);
                            return (
                                <p className="view-selector-button" ref={'view_selector' + view}>{view}</p>
                                );
                            }, this)}
                        </div>
                        <ScanHeatMap ref="heatmap" chart_name={this.props.name} handle_tooltip_select={this.handle_tooltip_select} />
                    </div>
                    <LineProfile ref="line_profile" chart_name={this.props.name}/>
                </div>
            );
        }
    });
    return ScanViewer;
});