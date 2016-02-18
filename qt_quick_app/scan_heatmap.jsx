define(["jquery", "react", "dom", "heatmap", "underscore", "console"], function($, React, ReactDOM, heatmap, _, console) {
    function asyncLoop(iterations, func, callback) {
        var index = 0;
        var done = false;
        var loop = {
            next: function() {
                if (done) {
                    return;
                }

                if (index < iterations) {
                    index++;
                    func(loop);

                } else {
                    done = true;
                    callback();
                }
            },

            iteration: function() {
                return index - 1;
            },

            break: function() {
                done = true;
                callback();
            }
        };
        loop.next();
        return loop;
    }

    var ScanHeatMap = React.createClass({ // http://jsfiddle.net/gh/get/jquery/1.9.1/highslide-software/highcharts.com/tree/master/samples/maps/demo/heatmap/
        getInitialState: function() {
            return {
                num_rendered: 0,
                data: []
            };
        },
        renderChart: function() {
            Highcharts.setOptions({
                plotOptions: {
                    series: {
                        animation: false
                    }
                }
            });
            var node = this.refs.chartNode.getDOMNode();
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    type: 'heatmap',
                    height: 400,
                    width: 400
                },
                title: {
                    text: 'Highcharts heat map',
                    align: 'left'
                },

                subtitle: {
                    text: 'Temperature variation by day and hour through May 2015',
                    align: 'left'
                },

                xAxis: {
                    min: 0,
                    max: 63
                },

                yAxis: {
                    title: {
                        text: null
                    },
                    // minPadding: 0,
                    // maxPadding: 0,
                    // startOnTick: false,
                    // endOnTick: false,
                    min: 0,
                    max: 63,
                },

                colorAxis: {
                    stops: [
                        [0, '#3060cf'],
                        [0.5, '#fffbbc'],
                        [0.9, '#c4463a']
                    ],
                },
                plotOptions: {
                    heatmap: {
                        animation: false, // doesnt seem to work
                    },
                    series: {
                        animation: false,
                    }
                },
                series: [{
                    borderWidth: 0,
                    data: [],
                    turboThreshold: Number.MAX_VALUE // #3404, remove after 4.0.5 release
                }]
            });
        });
        },
        asyncAddPoint: function(i, data, avg) {
            var self = this;
            setTimeout(function() {
                self.setState({
                    data: self.state.data.concat([[data[i], data[i+1], data[i+2] - avg]])
                });
            }, 0);
        },
        redrawChartWrapper: function() {
            _.defer(this.redrawChart).bind(this);
        },
        redrawChart: function() {
            this.state.chart.redraw();
        },
        handleNewDataWrapper: function(data) {
            console.log("called w");
            var self = this;
            setTimeout(function(){ self.handleNewData(data); }, 0);
        },
        handleNewData: function(data) {
            console.log("called");
            var self = this;
            var average = data.pop(); // remove the average from the array
            for (var i = 0; i < data.length; i += 3) {
                self.asyncAddPoint(i, data, average);
            }
            setTimeout(function() {
                self.state.chart.series[0].setData(self.state.data);
            }, 0);
            
            // _.defer(self.state.chart.series[0].setData(data)); // I think this get triggered just a little bit before the addPoint methods all return...
                                // That's why we have a separate redrawChart method that gets called at the end of scanning,
                                // to ensure the last points get drawn - maybe we can hook into the addpoint method or check
                                // the length of chart.series[0].data
        },
        componentDidMount: function() {
            this.renderChart();
            this.props.establishDataConnection(this.handleNewDataWrapper);
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            this.setState({
                chart: chart
            });
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    return <ScanHeatMap establishDataConnection={scanner.new_forward_offset_data.connect} finishSignal={scanner.all_data_received.connect}/>;
});
