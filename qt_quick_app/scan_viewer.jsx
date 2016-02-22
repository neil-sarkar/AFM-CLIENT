define(["react", "dom", "heatmap", "console", "jsx!pages/line_profile", "jsx!pages/scan_heatmap"], function(React, ReactDOM, heatmap, console, LineProfile, ScanHeatMap) {
    var ScanViewer = React.createClass({
        componentDidMount: function() {
            this.props.establishDataConnection(this.handle_new_data_wrapper);
        },
        handle_new_data_wrapper: function(data) {
            var self = this;
            setTimeout(function(){ self.handle_new_data(data); }, 0);            
        },
        handle_new_data: function(data) {
            var self = this;
            for (var i = 0; i < data.length; i += 3) {
                self.dispatch_data(data[i], data[i+1], data[i+2], (i === 0));
            }
            this.prompt_redraw();
            this.refs.line_profile.print_series();
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
        },
        render: function() {
            return (
                <div>
                    <ScanHeatMap ref="heatmap" chart_name="Forward Offset" handle_tooltip_select={this.handle_tooltip_select}/>
                    <LineProfile ref="line_profile" chart_name="Forward Offset"/>
                </div>
            );
        }
    });
    return ScanViewer;
});