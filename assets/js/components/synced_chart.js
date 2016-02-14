define(["jquery", "highcharts"], function($, highcharts) {
	var ChartData = function() {
		this.chart = null;
		this.zoom_padding = 300;
	};

	ChartData.prototype.add_data= function(data) {
		var two_d_data = [];
		var min_x = 100000;
        var max_x = 0;
        for (i = 0; i < data.length; i += 2) {
            min_x = data[i] < min_x  ? data[i] : min_x;
            max_x = data[i] > max_x  ? data[i] : max_x;
            two_dimensional_data.push([data[i], data[i+1]]);
        }
        var series = create_series(two_dimensional_data);
        this.zoom_extremes(series);
	};

	ChartData.prototype.zoom_extremes = function(sweep) {
		this.chart.addSeries(series);
        chart.xAxis[0].setExtremes(min_x - this.zoom_padding, max_x + this.zoom_padding);
	};

	function Chart() {
		this.chart = {
            zoomType: 'x',
        };
        this.title = {
            text: 'Phase'
        };
        this.tooltip = {
           crosshairs: [true, true]
        };
        this.xAxis = {
            type: 'linear',
            title: {
                text: "Frequency (Hz)"
            },
            events: {
                afterSetExtremes: function (event) {
                   if (!auto_populating) {
                       var xMin = event.min;
                       var xMax = event.max;
                       var ex = amplitude_chart.xAxis[0].getExtremes();
                       if (ex.min != xMin || ex.max != xMax) amplitude_chart.xAxis[0].setExtremes(xMin, xMax, true, false);
                   }
                }
            }
        };
        this.yAxis = {
            title: {
                text: 'AFM Phase (rad)'
            }
        };
        this.legend = {
            enabled: false
        };
        this.synced_charts = [];
        this.plotOptions = {
          series: {
              point: {
                  events: {
                      mouseOver: function () {
                          var index = this.index;
                          var series = this.series._i;
                      }
                  }
              },
           }
        };
        this.series = [{
            name: name,
            data: [[1,1],[2,2],[3,3],[4,4],[5,5]],
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
            },
        }];
    }
    

    ChartData.prototype.chart = chart();
    return ChartData;
});