$(function () {
    $('#container').highcharts({
        chart: {
            zoomType: 'x',
        },
        title: {
            text: 'Amplitude'
        },
        subtitle: {
                   text: 'Click and drag in the plot area to zoom in'
        },
        xAxis: {
            type: 'linear',
        },
        yAxis: {
            title: {
                text: 'AFM Amplitude'
            }
        },
        legend: {
            enabled: false
        },
    });
});

sweeper.new_amplitude_data.connect(addData);
//sweeper.new_phase_point.connect(test);

var sweep_number = 0;
var sweep_colors = ["#0066FF","#FF0000", "FF530D"];

function sweep() {
    sweeper.start_state_machine();
}

function addData(data) {
    var chart = $('#container').highcharts();
    var new_container = [];
    var min_x = 100000;
    var max_x = 0;
    for (i = 0; i < data.length; i += 2) {
        min_x = data[i] < min_x  ? data[i] : min_x;
        max_x = data[i] > max_x  ? data[i] : max_x;
        new_container.push([data[i], data[i+1]]);
    }
    console.log(new_container);
    var series = {
        name: "ADC",
        data: new_container,
        type: "area",
        color: sweep_colors[sweep_number],
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
    }
    $('#container').highcharts().addSeries(series);
    chart.xAxis[0].setExtremes(min_x, max_x);
    sweep_number += 1;
}


