define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var LineProfile = React.createClass({
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
                    text: "Line Profile"
                },
                tooltip: { crosshairs: [true, true] },
                xAxis: {
                    type: 'linear',
                },
                yAxis: {
                    title: {
                        text: 'Amplitude (V)'
                    },
                },
                legend: {
                    enabled: false
                },
                series: [ {
                    name: "height",
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
        handleNewData: function(profile_data) {
        },
        componentDidMount: function() {
            this.renderChart();
            this.props.establishDataConnection(this.handleNewData);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart profile", ref: "lineProfileNode"}));
        }
    });
    return <LineProfile establishDataConnection={scanner.new_forward_offset_data.connect}/>;
});
