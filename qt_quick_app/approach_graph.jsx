define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var ApproachGraph = React.createClass({
        renderChart: function() {
            var node = this.refs.chartNode;
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: '#EFEFEF',
                    height: 300,
                    type: 'line',
                    zoomType: 'x',
                },
                title: {
                    text: "Approach"
                },
                tooltip: { crosshairs: [true, true] },
                xAxis: {
                    type: 'datetime',
                },
                yAxis: {
                    title: {
                        text: 'Amplitude (V)'
                    }
                },
                line: {
                    marker: {
                        enabled: false
                    }
                },
                legend: {
                    enabled: false
                },
                series: [ {
                    name: "Z Piezoresistor Amplitude",
                    type: "area",
                    plotOptions: {
                        area: {
                            fillColor: {
                                linearGradient: {
                                    x1: 0,
                                    y1: 0,
                                    x2: 0,
                                    y2: 1
                                },
                                stops: [
                                    [0, Highcharts.getOptions().colors[0]],
                                    [1, Highcharts.Color(Highcharts.getOptions().colors[0]).setOpacity(0).get('rgba')]
                                ]
                            },
                            marker: {
                                radius: 2
                            },
                            lineWidth: 1,
                            states: {
                                hover: {
                                    lineWidth: 1
                                }
                            },
                            threshold: null
                        }
                    }
                }
                ],
            });
        });
        },
        handleNewData: function(approach_state, approach_adc_read) {
            // we don't use the appraoch state here...we use it in a separate dialog
            // might be worth refactoring the signal
            var node = this.refs.chartNode;
            var point = [(new Date()).getTime(), approach_adc_read];
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            $(node).highcharts().series[0].addPoint(point, true, num_points_displayed > 10, false);
        },

        update_plotline: function(value) {
            while (this.state.chart.yAxis[0].plotLinesAndBands.length) {
                this.state.chart.yAxis[0].removePlotLine('setpoint');
            }
            this.state.chart.yAxis[0].addPlotLine({
                // tried adding a label but it always hides behind the graph
                value: value,
                color: 'red',
                dashStyle: 'dash',
                width: 2,
                id: 'setpoint'
            });
        },
        start_streaming: function() {
            adc_5.value_changed.connect(this.handle_adc_value_changed);
            adc_stream_interval_id = setInterval(function() {
                adc_5.read();
            }, 500);
        },
        stop_streaming: function() {
            try {
                adc_5.value_changed.disconnect(this.handle_adc_value_changed);
            } catch (err) {
                console.log(err);
            }
            if (typeof adc_stream_interval_id !== 'undefined') {
                clearInterval(adc_stream_interval_id);
            }
        },
        handle_adc_value_changed: function(adc_value) {
            var node = this.refs.chartNode;
            var point = [(new Date()).getTime(), adc_value];
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            $(node).highcharts().series[0].addPoint(point, true, num_points_displayed > 10, false);
        },
        componentDidMount: function() {
            this.renderChart();
            var node = this.refs.chartNode;
            this.setState({
                chart: $(node).highcharts()
            });
            this.props.establishDataConnection(this.handleNewData);
            pid.setpoint_changed.connect(this.update_plotline);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
            var that = this;
            setTimeout(function() {
                that.update_plotline(pid.setpoint);
            }, 1000);
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    return ApproachGraph;
});
