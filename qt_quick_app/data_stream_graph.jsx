define(["jquery", "react", "dom", "highcharts", "console", "constants", "canvasjs"], function($, React, ReactDOM, highcharts, console, Constants, CanvasJS) {
    var x = 0;
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
                    padding: 5
                },
                data: [{
                    type: "line",
                    color: Constants.Approach_Amplitude_Data_Color,
                    dataPoints: self.state.data,
                    markerType: "none",
                }],
                axisY: {
                    stripLines: [{
                        value: self.props.plotline_default,
                        color: Constants.Approach_Amplitude_Strip_Line_Color,
                        lineDashType: "dash",
                        label: "Setpoint",
                        labelFontColor: "#606060",
                        labelBackgroundColor: "transparent",
                    },
                    {  // just for a background color effect
                        startValue: -5,
                        endValue: 5,
                        color:"#EFEFEF",
                    }],
                    labelFontFamily: Constants.System_Font,
                    labelFontSize: 11,
                    maximum: self.props.max_value,
                    gridColor: "#DFDFDF",
                    gridThickness: 1,
                    tickLength: 0,
                    lineThickness: 0,
                },
                axisX: {
                    lineThickness: 0,
                    tickThickness: 0,
                    valueFormatString: " ",
                },
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
            var stream_interval_id = setInterval(function() {
                this.props.prompt_read();
            }.bind(this), this.props.poll_rate);
            this.setState({
                interval_id: stream_interval_id,
            });
        },
        stop_streaming: function() {
            clearInterval(this.state.interval_id);
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

