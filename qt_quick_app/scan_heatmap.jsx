define(["jquery", "react", "dom", "heatmap"], function($, React, ReactDOM, highcharts) {
    var ScanHeatMap = React.createClass({ // http://jsfiddle.net/gh/get/jquery/1.9.1/highslide-software/highcharts.com/tree/master/samples/maps/demo/heatmap/
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
                    categories: Array.apply(null, Array(256)).map(function (_, i) {return i;})
                },

                yAxis: {
                    title: {
                        text: null
                    },
                    // minPadding: 0,
                    // maxPadding: 0,
                    // startOnTick: false,
                    // endOnTick: false,
                    // tickWidth: 1,
                    categories: Array.apply(null, Array(256)).map(function (_, i) {return i;})
                },

                colorAxis: {
                    stops: [
                        [0, '#3060cf'],
                        [0.5, '#fffbbc'],
                        [0.9, '#c4463a']
                    ],
                },

                series: [{
                    borderWidth: 0,
                    data: []
                }]
            });
        });
        },
        handleNewData: function(data) {
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts()
            var z_value_sum = data.reduce(function(previousValue, currentValue, currentIndex, array) {
              return (currentIndex + 1) % 3 == 0 ? previousValue + currentValue : previousValue;
            }, 0); // 0 is the initial value parameter, which would be set to the first element if not specified

            var z_value_avg = z_value_sum / (data.length / 3);
            for (var i = 0; i < data.length; i += 3) {
                chart.series[0].addPoint([data[i], data[i+1], data[i+2] - z_value_avg], false);
            }
            console.log(data);
            chart.redraw();
        },
        componentDidMount: function() {
            this.renderChart();
            var node = this.refs.chartNode.getDOMNode();
            this.props.establishDataConnection(this.handleNewData);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    return <ScanHeatMap establishDataConnection={scanner.new_forward_offset_data.connect}/>;
});
