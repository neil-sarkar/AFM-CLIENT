define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var ForceCurve = React.createClass({
        renderChart: function() {
            var node = this.refs.chartNode.getDOMNode();
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: '#EFEFEF',
                    height: 800,
                    type: 'line',
                    zoomType: 'x',
                },
                title: {
                    text: "Force Curve"
                },
                tooltip: { crosshairs: [true, true] },
                xAxis: {
                    type: 'linear',
                },
                yAxis: [{ // Primary yAxis
                        title: {
                            text: 'Amplitude',
                        },
                    }, { // Secondary yAxis
                        title: {
                            text: 'Phase',
                        },
                }],
                line: {
                    marker: {
                        enabled: false
                    }
                },
                legend: {
                    enabled: false
                },
                series: [],
            });
        });
        },
        add_series: function() {
            return {
                type: "line",
                data: [],
            };
        },
        handleNewData: function() {
            // we don't use the appraoch state here...we use it in a separate dialog
            // might be worth refactoring the signal
            var node = this.refs.chartNode.getDOMNode();
            var point = [(new Date()).getTime(), approach_adc_read];
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            $(node).highcharts().series[0].addPoint(point, true, num_points_displayed > 10, false);
        },
        handle_new_approaching_amplitude_data: function(data) {
            var new_series = this.add_series();
            new_series.name = "Approaching amplitude";
            new_series.yAxis = 0;
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            chart.addSeries(new_series);
            for (var i = 0; i < data.length; i += 2) {
                chart.series[chart.series.length - 1].addPoint([data[i], data[i+1]], false);
            }
        },
        handle_new_approaching_phase_data: function(data) {
            var new_series = this.add_series();
            new_series.name = "Approaching phase";
            new_series.yAxis = 1;
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            chart.addSeries(new_series);
            for (var i = 0; i < data.length; i += 2) {
                chart.series[chart.series.length - 1].addPoint([data[i], data[i+1]], false);
            }
        },
        handle_new_retracting_amplitude_data: function(data) {
            var new_series = this.add_series();
            new_series.name = "Retracting amplitude";
            new_series.yAxis = 0;
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            chart.addSeries(new_series);
            for (var i = 0; i < data.length; i += 2) {
                chart.series[chart.series.length - 1].addPoint([data[i], data[i+1]], false);
            }
        },
        handle_new_retracting_phase_data: function(data) {
            var new_series = this.add_series();
            new_series.name = "Retracting phase";
            new_series.yAxis = 1;
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            chart.addSeries(new_series);
            for (var i = 0; i < data.length; i += 2) {
                chart.series[chart.series.length - 1].addPoint([data[i], data[i+1]], false);
            }
            chart.redraw(false, false);
        },
        componentDidMount: function() {
            this.renderChart();
            afm.new_approaching_amplitude_data.connect(this.handle_new_approaching_amplitude_data);
            afm.new_approaching_phase_data.connect(this.handle_new_approaching_phase_data);
            afm.new_retracting_amplitude_data.connect(this.handle_new_retracting_amplitude_data);
            afm.new_retracting_phase_data.connect(this.handle_new_retracting_phase_data);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    
    var ForceCurveViewer = React.createClass({
        render: function() {
            return (
                <div>
                    <ForceCurve />
                    <button className="action-button" onClick={afm.cmd_generate_force_curve}>Generate</button>
                </div>
            )
        }
    });

    ReactDOM.render(<ForceCurveViewer />, document.getElementById('content'));
});
