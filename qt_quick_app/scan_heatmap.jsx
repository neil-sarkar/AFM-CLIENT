define(["jquery", "react", "dom", "heatmap", "exporting", "exporting_offline", "console", "underscore"], function($, React, ReactDOM, heatmap, exporting, offline_exporting, console, _) {
    var ScanHeatMap = React.createClass({ // http://jsfiddle.net/gh/get/jquery/1.9.1/highslide-software/highcharts.com/tree/master/samples/maps/demo/heatmap/
        renderChart: function() {
            Highcharts.setOptions({
                plotOptions: {
                    series: {
                        animation: false
                    }
                }
            });
            var node = this.refs.chartNode;
            var self = this;
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    type: 'heatmap',
                    height: 400,
                    width: 475,
                },
                title: {
                    text: self.props.chart_name,
                },

                xAxis: {
                    min: 1,
                    max: 256,
                    endOnTick: false
                },

                yAxis: {
                    min: 1,
                    max: 256,
                    endOnTick: false
                },
                colorAxis: {
                    stops: [
                        [0, '#000000'],
                        [0.33, "#581C00"],
                        [0.66, "#bc8000"],
                        [1, '#FcFc80']
                    ],
                },
                legend: {
                    align: 'right',
                    layout: 'vertical',
                    margin: 0,
                    verticalAlign: 'middle',
                    y: 25,
                    symbolHeight: 280
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
            console.log("wrapper entered", data[0]);
            var self = this;
            setTimeout(function(){ self.handleNewData(data); }, 0);
        },
        handleNewData: function(data) {
            console.log("handling new data", data[0]);
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
            while (this.state.chart.series.length - 1)
                this.state.chart.series[0].remove(false);
            this.state.chart.series[0].setData([]);
        },
        redraw: function() {
            this.state.chart.redraw();
        },
        eliminate_outliers: function(min_cutoff, max_cuttoff) {
            this.state.chart.addSeries({
                borderWidth: 0,
                data: [],
                turboThreshold: Number.MAX_VALUE // #3404, remove after 4.0.5 release
            });
            var array = this.state.chart.series[0].data;
            var sample_min = Number.POSITIVE_INFINITY; // these will store the absolute mins and maxes post proces
            var sample_max = Number.NEGATIVE_INFINITY;
            for (var i = 0; i < array.length; i++ ) {
                // COPY x y and z values for the point
                var x = array[i].x;
                var y = array[i].y;
                var curr_value = array[i].value;
                if (curr_value > max_cuttoff) {
                    curr_value = max_cuttoff;
                } else if (curr_value < min_cutoff) {
                    curr_value = min_cutoff;
                }
                sample_min = Math.min(sample_min, curr_value);
                sample_max = Math.max(sample_max, curr_value);
                this.state.chart.series[this.state.chart.series.length - 1].addPoint({x: x, y: y, value: curr_value}, false, false);
            }
            this.state.chart.colorAxis[0].setExtremes(sample_min, sample_max);
            console.log(this.state.chart.xAxis[0]);
            this.state.chart.redraw();
            for (var j = 0; j < this.state.chart.series.length - 1; j++)
                this.state.chart.series[j].hide();

            console.log("Done removing outliers");
        },
        change_num_rows: function(max_value) {
            this.state.chart.yAxis[0].setExtremes(1, max_value);
        },
        change_num_columns: function(max_value) {
            this.state.chart.xAxis[0].setExtremes(1, max_value);
        },
        componentDidMount: function() {
            this.renderChart();
            scanner.num_rows_changed.connect(this.change_num_rows);
            scanner.num_columns_changed.connect(this.change_num_columns);
            // this.props.newScan(this.erase_data);
            var node = this.refs.chartNode;
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
