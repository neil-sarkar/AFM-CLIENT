define(["jquery", "highcharts"], function($, highcharts) {

    sweeper.new_sweep_data.connect(add_data);

    function back() {
        main_window.load_home_page();
    }

    var sweep_number = 0;
    var sweep_colors = ["#0066FF","#FF0000", "FF530D"];
    var amplitude_chart;
    var phase_chart;
    var auto_populating;

    function sync_tooltips(index, series, e) {
        var phase_point = phase_chart.series[series].points[index];
        var amplitude_point = amplitude_chart.series[series].points[index];
        phase_chart.tooltip.refresh(phase_point);
        amplitude_chart.tooltip.refresh(amplitude_point);
        amplitude_chart.xAxis[0].drawCrosshair(e, amplitude_point);
        phase_chart.xAxis[0].drawCrosshair(e, phase_point);
        amplitude_chart.yAxis[0].drawCrosshair(e, amplitude_point);
        phase_chart.yAxis[0].drawCrosshair(e, phase_point);
    }

    function sweep() {
        auto_populating = true;
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
                        linearGradie    nt: {
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
        sweep_number = (sweep_number + 1) % 3;
        if (sweep_number == 0)
            auto_populating = false;
    }

    function add_data(amplitude_data, phase_data) {
        update_chart(amplitude_chart, amplitude_data, "Amplitude (V)");
        update_chart(phase_chart, phase_data, "Phase (rad)");
    }

    $('text:contains("Highcharts.com")').hide();
});



