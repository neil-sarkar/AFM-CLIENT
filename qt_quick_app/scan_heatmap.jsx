define(["jquery", "react", "dom", "heatmap", "console", "underscore"], function($, React, ReactDOM, heatmap, console, _) {
    var ScanHeatMap = React.createClass({ // http://jsfiddle.net/gh/get/jquery/1.9.1/highslide-software/highcharts.com/tree/master/samples/maps/demo/heatmap/
        renderChart: function() {
            Highcharts.setOptions({
                plotOptions: {
                    series: {
                        animation: false
                    }
                }
            });
            var node = this.refs.chartNode.getDOMNode();
            var self = this;
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    type: 'heatmap',
                    height: 400,
                    width: 400,
                },
                title: {
                    text: self.props.chart_name,
                },

                xAxis: {
                    min: 0,
                    max: 256
                },

                yAxis: {
                    min: 0,
                    max: 256,
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
                        events: {
                            click: function(e) {
                                self.props.handle_tooltip_select(e.point.y);
                            }
                        }
                    },
                },
                series: [{
                    borderWidth: 0,
                    data: [],
                    turboThreshold: Number.MAX_VALUE // #3404, remove after 4.0.5 release
                }]
            });
        });
        },
        asyncAddPoint: function(x, y, z) {
            this.state.chart.series[0].addPoint([x, y, z], false); // add point WITHOUT redrawing or animating
        },
        handleNewDataWrapper: function(data) {
            var self = this;
            setTimeout(function(){ self.handleNewData(data); }, 0);
        },
        handleNewData: function(data) {
            var self = this;
            var add_point = this.state.chart.series[0].addPoint;
            for (var i = 0; i < data.length; i += 3) {
                self.asyncAddPoint(add_point, i, data);
            }
            setTimeout(function() {
                self.state.chart.redraw(false);
            }, 0);
        },
        erase_data: function() {
            this.state.chart.series[0].setData([]);
        },
        redraw: function() {
            this.state.chart.redraw();
        },
        eliminate_outliers: function() {
            console.log("called");
            var array = this.state.chart.series[0].data;
            var mean = _.reduce(array, function(memo, num) {
                            return memo + num.value;
                        }, 0) / (array.length === 0 ? 1 : array.length);

            var dev = array.map(function(itm){return (itm.value - mean)*(itm.value - mean);});
            var std_dev = Math.sqrt(dev.reduce(function(a, b){return a+b;})/array.length);
            console.log(mean, std_dev);
            for (var i = 0; i < array.length; i++ ) {
                var curr_value = this.state.chart.series[0].data[i].value;
                if (curr_value > mean + 2 * std_dev)
                    this.state.chart.series[0].data[i].update({value: mean + 2 * std_dev}, false, false);
                else if (curr_value < mean - 2 * std_dev)
                    this.state.chart.series[0].data[i].update({value: mean - 2 * std_dev}, false, false);
            }
            this.state.chart.redraw();
            console.log("done");
        },
        componentDidMount: function() {
            this.renderChart();
            // this.props.establishDataConnection(this.handleNewDataWrapper);
            // this.props.newScan(this.erase_data);
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
    return ScanHeatMap;
});
