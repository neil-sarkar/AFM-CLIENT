define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var ZFineGraph = React.createClass({
        renderChart: function() {
            var node = this.refs.chartNode.getDOMNode();
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: '#EFEFEF',
                    height: 300,
                    type: 'line',
                    zoomType: 'x',
                },
                title: {
                    text: "Z Fine"
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
                                enabled: false
                            },
                            lineWidth: 1,
                            states: {
                                hover: {
                                    lineWidth: 1
                                }
                            },
                            threshold: null
                        },
                        line : {
                            marker: {
                                enabled: false
                            }
                        }
                    }
                }
                ],
            });
        });
        },
        handleNewData: function(dac_value) {
            var node = this.refs.chartNode.getDOMNode();
            var point = [(new Date()).getTime(), dac_value];
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            $(node).highcharts().series[0].addPoint(point, true, num_points_displayed > 10, false);
        },
        componentDidMount: function() {
            this.renderChart();
            var node = this.refs.chartNode.getDOMNode();
            this.setState({
                chart: $(node).highcharts()
            });
            this.props.establishDataConnection(this.handleNewData);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
            var that = this;
        },
        start_streaming: function() {
            z_fine_interval_id = setInterval(function() {
                dac_6.cmd_read_value();
            }, 500);
        },
        stop_streaming:function() {
            if (typeof z_fine_interval_id !== 'undefined')
                clearInterval(z_fine_interval_id);
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    return ZFineGraph;
});