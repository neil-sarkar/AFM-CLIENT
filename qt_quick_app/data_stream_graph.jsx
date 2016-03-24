define(["jquery", "react", "dom", "highcharts", "console", "constants", "canvasjs"], function($, React, ReactDOM, highcharts, console, Constants, CanvasJS) {
    var x = 0;
    var stream_interval_id;
    var ApproachGraph = React.createClass({
        getDefaultProps: function() {
            return {
                plotline_default: Number.NEGATIVE_INFINITY,
            };
        },
        getInitialState: function() {
            return {
                data: []
            };
        },
        init_chart: function() {
            var self = this;
            var chart = new CanvasJS.Chart(this.refs.chartNode, {
                title: {
                    text: self.props.chart_title,
                    fontFamily: Constants.System_Font,
                    fontSize: Constants.Approach_Amplitude_Font_Size,
                    padding: 10,
                },
                data: [{
                    type: "line",
                    color: Constants.Approach_Amplitude_Data_Color,
                    dataPoints: self.state.data
                }],
                axisY: {
                    stripLines: [{
                        value: self.props.plotline_default,
                        color: Constants.Approach_Amplitude_Strip_Line_Color,
                        lineDashType: "dash",
                    }],
                    labelFontFamily: Constants.System_Font,
                    labelFontSize: 11,
                },
                axisX: {
                    lineThickness: 0,
                    tickThickness: 0,
                    valueFormatString: " ",
                }
            });
            this.setState({
                chart: chart
            });
        },
        add_data: function(value) {
            if (this.state.data.length < this.props.num_points_displayed) {
                this.state.data.push({x: x, y: value});
            } else {
                this.state.data.shift({x: x, y: value});
            }
            x += 1;
            this.state.chart.render();
            if (this.state.data.length === 1) {
                $('.canvasjs-chart-credit').hide(); // TODO: put this in a more appropriate place
            }
        },
        update_plotline: function(new_value) {
            this.state.chart.options.axisY.stripLines[0].value = new_value;
        },
        componentDidMount: function() {
            this.init_chart();
            this.props.data_update_signal.connect(this.handle_new_data);
            if (typeof this.props.plotline_update_signal !== 'undefined')
                this.props.plotline_update_signal.connect(this.update_plotline);
        },
        start_streaming: function() {
            stream_interval_id = setInterval(function() {
                this.props.prompt_read();
            }.bind(this), Constants.Approach_Poll_Rate);
        },
        stop_streaming: function() {
            if (typeof stream_interval_id !== 'undefined') {
                clearInterval(stream_interval_id);
            }
        },
        handle_new_data: function(value) {
            this.add_data(value);
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode", id: this.props.dom_id}));
        }
    });
    return ApproachGraph;
});

