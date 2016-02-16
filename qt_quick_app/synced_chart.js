define(["jquery", "highcharts"], function($, highcharts) {
//    HighCharts.prototype = {
//        sync: function() {
//            // iterate through all charts
//        }
//    }
    var chart = {
        chart: { zoomType: 'x' },
        title: { text: 'Amplitude' },
        tooltip: { crosshairs: [true, true] },
        xAxis: {
            type: 'linear',
            title: { text: "Frequency (Hz)" },
        },
        yAxis: {
            title: {
                text: 'Amplitude (V)'
            },
        },
        legend: {
            enabled: false
        },
        plotOptions: {
           series: {
               point: {
                   events: {
                       mouseOver: function () {
                       }
                   }
               },
            }
        }
    }
    return chart;
}
