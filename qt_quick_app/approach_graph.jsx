define(["jquery", "react", "dom", "highcharts", "console", "constants"], function($, React, ReactDOM, highcharts, console, Constants) {
    var ApproachGraph = React.createClass({
        renderChart: function() {
            var node = this.refs.chartNode;
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: '#EFEFEF',
                    height: 300,
                    type: 'line',
                },
                title: {
                    text: "Approach"
                },
                tooltip: {
                    // crosshairs: [true, true],
                    formatter: function() {
                        return '<b>'+ $(node).highcharts().series[0].name +'</b>: ' + this.point.y.toFixed(4);
                    },
                    enabled: false,
                },
                xAxis: {
                    labels: {
                      enabled: false
                    },
                },
                yAxis: {
                    title: {
                        text: 'Amplitude'
                    },
                    minPadding: 20,
                    minRange: 0.5,
                },
                legend: {
                    enabled: false
                },
                plotOptions: {
                    line: {
                        marker: {
                            enabled: false
                        }
                    }
                },
                series: [ {
                    name: "Z Piezoresistor Amplitude",
                    // type: "area",
                    // plotOptions: {
                    //     area: {
                    //         fillColor: {
                    //             linearGradient: {
                    //                 x1: 0,
                    //                 y1: 0,
                    //                 x2: 0,
                    //                 y2: 1
                    //             },
                    //             stops: [
                    //                 [0, Highcharts.getOptions().colors[0]],
                    //                 [1, Highcharts.Color(Highcharts.getOptions().colors[0]).setOpacity(0).get('rgba')]
                    //             ]
                    //         },
                    //         marker: {
                    //             enabled: true,
                    //         },
                    //         lineWidth: 1,
                    //         threshold: null
                    //     }
                    // }
                }
                ],
            });
        });
        },
        handleNewData: function(approach_state, approach_adc_read) {
            // we don't use the appraoch state here...we use it in a separate dialog
            // might be worth refactoring the signal
            var node = this.refs.chartNode;
            var point = approach_adc_read;
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            this.shift_add_point(point, num_points_displayed);
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
            }, Constants.Approach_Poll_Rate);
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
        shift_add_point: function(point, num_points_displayed) {
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            chart.series[0].addPoint(point, true, num_points_displayed > Constants.Approach_Num_Points_Displayed, false);
        },
        handle_adc_value_changed: function(adc_value) {
            var node = this.refs.chartNode;
            var point = adc_value;
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            this.shift_add_point(point, num_points_displayed);
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
