define(["jquery", "highcharts"], function($, highcharts) {
	var chart = {
		chart: {
            zoomType: 'x',
        },
        title: {
            text: 'Phase'
        },
        tooltip: {
           crosshairs: [true, true]
        },
        xAxis: {
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
        },
        yAxis: {
            title: {
                text: 'AFM Phase (rad)'
            }
        },
        legend: {
            enabled: false
        },
        plotOptions: {
          series: {
              point: {
                  events: {
                      mouseOver: function () {
                          var chart = this.series.chart;
                          var index = this.index;
                          var series = this.series._i;
                          sync_tooltips(index, series);
                      }
                  }
              },
           }
        }
    };
    return chart;
});