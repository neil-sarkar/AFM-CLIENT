define(["jquery", "react", "dom", "heatmap", "highcharts_canvas"], function($, React, ReactDOM, highcharts, heatmap) {
    var ScanHeatMap = React.createClass({ // http://jsfiddle.net/gh/get/jquery/1.9.1/highslide-software/highcharts.com/tree/master/samples/maps/demo/heatmap/
        getInitialState: function() {
            return {
                num_rendered: 0
            };
        },
        renderChart: function() {
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
        handleNewData: function(data) {
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            // var z_value_sum = data.reduce(function(previousValue, currentValue, currentIndex, array) {
            //   return (currentIndex + 1) % 3 == 0 ? previousValue + currentValue : previousValue;
            // }, 0); // 0 is the initial value parameter, which would be set to the first element if not specified
            
            chart.redraw();
        },
        componentDidMount: function() {
            this.renderChart();
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            this.props.establishDataConnection(this.handleNewData);
            for (var i = 0; i < 63; i += 1) {
                for (var j = 0; j < 63; j += 1)
                chart.series[0].addPoint([i, j, 0], false);
            }
            chart.redraw();
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    return <ScanHeatMap establishDataConnection={scanner.new_forward_offset_data.connect}/>;
});