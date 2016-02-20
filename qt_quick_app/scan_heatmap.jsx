define(["jquery", "react", "dom", "heatmap", "underscore", "console", "jsx!pages/line_profile"], function($, React, ReactDOM, heatmap, _, console, LineProfile) {
    var ScanViewer = React.createClass({
        render: function() {
            return (
                <div>
                    <ScanHeatMap ref="heatmap" chart_name="Forward Offset" establishDataConnection={this.props.establishDataConnection} newScan={this.props.newScan}/>
                    <LineProfile ref="line_profile" chart_name="Forward Offset" establishDataConnection={this.props.establishDataConnection} newScan={this.props.newScan}/>
                </div>
            );
        }
    });


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
                    width: 400
                },
                title: {
                    text: self.props.chart_name,
                },

                xAxis: {
                    min: 0,
                    max: 127
                },

                yAxis: {
                    min: 0,
                    max: 127,
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
        asyncAddPoint: function(add_point, i, data) {
            var self = this;
            setTimeout(function() {
                self.state.chart.series[0].addPoint([data[i], data[i+1], data[i+2]], false, false); // add point WITHOUT redrawing or animating
            }, 0);
        },
        redrawChart: function() {
            this.state.chart.redraw();
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
        componentDidMount: function() {
            this.renderChart();
            this.props.establishDataConnection(this.handleNewDataWrapper);
            this.props.newScan(this.erase_data);
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
    // return ScanViewer;
    return ScanViewer;
});
