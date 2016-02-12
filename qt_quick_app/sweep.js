$(function () {
    $('#amplitude-chart-container').highcharts({
        chart: {
            zoomType: 'x',
        },
        title: {
            text: 'Amplitude'
        },
        tooltip: {
           crosshairs: [true, true]
        },
        xAxis: {
            type: 'linear',
            title: {
               text: "Frequency (Hz)"
            },
        },
        yAxis: {
            title: {
                text: 'Amplitude (V)'
            },
        },
        legend: {
            enabled: false
        },
    });
});
$(function () {
    $('#phase-chart-container').highcharts({
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
    });
});


sweeper.new_sweep_data.connect(add_data);
//sweeper.new_phase_point.connect(test);

var sweep_number = 0;
var sweep_colors = ["#0066FF","#FF0000", "FF530D"];
var amplitude_chart;
var phase_chart;

function sweep() {
    amplitude_chart = $('#amplitude-chart-container').highcharts();
    phase_chart = $('#phase-chart-container').highcharts();
    while (amplitude_chart.series.length > 0) { // remove any existing data
        amplitude_chart.series[0].remove(true);
        phase_chart.series[0].remove(true);
    }
    sweeper.start_state_machine();
}

function package_data(data) {

//    return {min: min_x, max: max_x, data: two_dimensional_data};
}

function create_series(input_data, name) {
    return {
        name: name,
        data: input_data,
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
}

function update_chart(chart, data, name) {
    console.log("updating chart");
    var packaged_data = package_data(data);
    var two_dimensional_data = [];
    var min_x = 100000;
    var max_x = 0;
    for (i = 0; i < data.length; i += 2) {
        min_x = data[i] < min_x  ? data[i] : min_x;
        max_x = data[i] > max_x  ? data[i] : max_x;
        two_dimensional_data.push([data[i], data[i+1]]);
    }
    var series = create_series(two_dimensional_data);
    chart.addSeries(series);
    chart.xAxis[0].setExtremes(min_x - 300, max_x + 300);
    sweep_number += 1;
}

function add_data(amplitude_data, phase_data) {
    update_chart(amplitude_chart, amplitude_data, "Amplitude (V)");
    update_chart(phase_chart, phase_data, "Phase (rad)");
}


