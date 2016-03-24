define(["jquery", "react", "dom", "highcharts", "console", "constants", "canvasjs"], function($, React, ReactDOM, highcharts, console, Constants, CanvasJS) {
    var chart;
    var data = [];
    var x = 0;
    var stream_interval_id;
    var ApproachGraph = React.createClass({
        add_data: function(value) {
            x += 1;
            if (data.length < this.props.num_points_displayed)
                data.push({x: x, y: value});
            else
                data.shift({x: x, y: value});
            
            chart.render();
        },
        init_chart: function() {
            chart = new CanvasJS.Chart(this.refs.chartNode, {
                title: {
                    text: "Approach"
                },
                data: [{
                    type: "line",
                    dataPoints: data
                }]
            });
        },
        componentDidMount: function() {
            this.init_chart();
            this.props.notify_signal.connect(this.handle_new_data);
        },
        start_streaming: function() {
            stream_interval_id = setInterval(function() {
                this.props.prompt_read();
            }.bind(this), Constants.Approach_Poll_Rate);
        },
        stop_streaming: function() {
            // try {
            //     this.props.notify_signal.disconnect(this.handle_new_data);
            // } catch (err) {
            //     console.log(err);
            // }
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

