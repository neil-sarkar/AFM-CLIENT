define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var ForceCurve = React.createClass({
        renderChart: function() {
            var node = this.refs.chartNode;
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: Constants.Graph_Background_Color,
                    height: 500,
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
                        opposite: true
                }],
                line: {
                    marker: {
                        enabled: false
                    }
                },
                legend: {
                    layout: 'vertical',
                    align: 'left',
                    verticalAlign: 'top',
                    borderWidth: 0,
                    floating: true,
                    y: 36,
                    x: 53
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
            var node = this.refs.chartNode;
            var point = [(new Date()).getTime(), approach_adc_read];
            var num_points_displayed = $(node).highcharts().series[0].data.length;
            $(node).highcharts().series[0].addPoint(point, true, num_points_displayed > 10, false);
        },
        handle_new_approaching_amplitude_data: function(data) {
            var new_series = this.add_series();
            new_series.name = "Approaching amplitude";
            new_series.yAxis = 0;
            var node = this.refs.chartNode;
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
            var node = this.refs.chartNode;
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
            var node = this.refs.chartNode;
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
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            chart.addSeries(new_series);
            for (var i = 0; i < data.length; i += 2) {
                chart.series[chart.series.length - 1].addPoint([data[i], data[i+1]], false);
            }
            chart.redraw(false, false);
        },
        clear: function() {
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            while (chart.series.length)
                chart.series[0].remove(false);
            chart.redraw();
        },
        componentDidMount: function() {
            this.renderChart();
            force_curve_generator.new_approaching_amplitude_data.connect(this.handle_new_approaching_amplitude_data);
            force_curve_generator.new_approaching_phase_data.connect(this.handle_new_approaching_phase_data);
            force_curve_generator.new_retracting_amplitude_data.connect(this.handle_new_retracting_amplitude_data);
            force_curve_generator.new_retracting_phase_data.connect(this.handle_new_retracting_phase_data);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart", ref: "chartNode"}));
        }
    });
    
    var ForceCurveViewer = React.createClass({
        clear: function() {
            this.refs.chart.clear();
        },
        save_data: function() {
            afm.save_force_curve_data();
        },
        generate: function() {
            pid.set_disabled();
            force_curve_generator.cmd_generate_force_curve();
        },
        render: function() {
            return (
                <div>
                    <ForceCurve ref="chart"/>
                    <div className="top-row" style={{width: "50%"}}>
                        <button className="action-button" onClick={this.generate}>Generate</button>
                        <button className="action-button" onClick={this.clear}>Clear</button>
                        <button className="action-button" onClick={this.save_data}>Save</button>
                    </div>
                </div>
            )
        }
    });

    ReactDOM.render(<ForceCurveViewer />, document.getElementById('content'));
});
