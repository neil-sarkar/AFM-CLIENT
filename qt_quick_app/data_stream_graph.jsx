define(["jquery", "react", "dom", "highcharts", "console", "constants", "canvasjs"], function($, React, ReactDOM, highcharts, console, Constants, CanvasJS) {
    var chart;
    var data = [];
    var x = 0;
    var stream_interval_id;
    var ApproachGraph = React.createClass({
        init_chart: function() {
            var self = this;
            chart = new CanvasJS.Chart(this.refs.chartNode, {
                title: {
                    text: "Approach"
                },
                data: [{
                    type: "line",
                    dataPoints: data
                }],
                axisY: {
                    stripLines: [
                    {
                        value: this.props.plotline_default,
                        color: "red",
                        lineDashType: "dash",
                    }
                    ]
                },
                axisX: {
                    lineThickness: 0,
                    tickThickness:0,
                    valueFormatString: " ",
                }
            });
        },
        add_data: function(value) {
            if (data.length < this.props.num_points_displayed) {
                data.push({x: x, y: value});
            } else {
                data.shift({x: x, y: value});
            }
            x += 1;
            chart.render();
        },
        update_plotline: function(new_value) {
            chart.options.axisY.stripLines[0].value = new_value;
        },
        componentDidMount: function() {
            this.init_chart();
            this.props.data_update_signal.connect(this.handle_new_data);
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
        handle_new_data: function(adc_value) {
            this.add_data(adc_value);
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    return ApproachGraph;
});

