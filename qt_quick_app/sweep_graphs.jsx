define(["jquery", "react", "dom", "highcharts", "console", "constants"], function($, React, ReactDOM, highcharts, console, Constants) {
    var SweepGraph = React.createClass({
        renderChart: function() {
            var node = this.refs.chartNode;
            var siblings = $(node).siblings(); // these are the graphs with which we want to sync our tooltip and zoom
            var dataSeries = this.state.model;
            var series = this.generate_initial_series();
            var self = this;
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: Constants.Graph_Background_Color,
                    height: 300,
                    type: 'line',
                    zoomType: 'x',
                },
                title: {
                    text: this.props.title
                },
                tooltip: { crosshairs: [true, true], valueDecimals: 4 },
                xAxis: {
                    type: 'linear',
                    title: { text: "Frequency (Hz)" },
                    events: {
                        afterSetExtremes: function (event) {
                            var xMin = event.min;
                            var xMax = event.max;

                            for (var i = 0; i < siblings.length; i += 1) {
                                var chart = $(siblings[i]).highcharts();
                                var ex = chart.xAxis[0].getExtremes();
                                if (ex.min != xMin || ex.max != xMax)
                                        chart.xAxis[0].setExtremes(xMin, xMax, true, false);
                            }
                        }
                    },
                },
                yAxis: {
                    title: {
                        text: this.props.ylabel
                    },
                },
                legend: {
                    enabled: false
                },
                exporting: {
                    enabled: false
                },
                credits: {
                    enabled: false
                },
                series: series,
                plotOptions: {
                    series: {
                        point: {
                            events: {
                                mouseOver: function (e) {
                                    // sync the tooltips of all sibling graphs
                                    var index = this.index;
                                    var series = this.series._i;
                                    self.props.emit_tooltip(index, series, e);
                                },
                                mouseOut: function(e) {
                                    self.props.emit_tooltip_hide();
                                },
                                click: function(e) {
                                    self.props.handle_click(e.point.x, this.index, this.series._i); // capture the y value
                                }
                            }
                        }
                    }
                }
            });
        },
        generate_initial_series : function() {
            var series_skeleton = {
            };
            var series = [];
            for (var i = 0; i < this.state.model; i += 1) {
                    var series_with_data = series_skeleton;
                    series_with_data.data = this.state.model[i];
                    series.push(series_with_data);
            }
            return series;
        },
        getInitialState: function() {
            return {
                model: []
            };
        },
        getDefaultProps: function() {
            return {
                zoom_buffer: 300,
            };
        },
        shouldComponentUpdate: function(nextProps, nextState) {
            return (nextProps.model || false) && nextProps.model.length > 0; // should we update the component?
        },
        componentDidMount: function() {
            this.renderChart();
            this.props.data_connection.connect(this.handle_new_data);
            this.props.DDS_set.connect(this.handle_new_DDS_freq);
        },
        handle_new_data: function(data) {
            var two_dimensional_data = [];
            var min_x = 100000;
            var max_x = 0;
            for (i = 0; i < data.length; i += 2) {
                min_x = data[i] < min_x  ? data[i] : min_x;
                max_x = data[i] > max_x  ? data[i] : max_x;
                two_dimensional_data.push([data[i], data[i+1]]); // parse x, y coordinates 
            }

            // var color = $(node).highcharts().series.length < 3 ? "blue" : "black";
            this.add_series(two_dimensional_data, "black");
            
            // TODO: check if this does anything
            this.state.model.push([]);
            (this.state.model[this.state.model.length - 1]).push(two_dimensional_data);
            $(node).highcharts().xAxis[0].setExtremes(min_x - this.props.zoom_buffer, max_x + this.props.zoom_buffer);
        },
        handle_new_DDS_freq: function(data) {
            var node = this.refs.chartNode;
            $(node).highcharts().xAxis[0].removePlotLine('DDS-Frequency-Indicator');
            $(node).highcharts().xAxis[0].addPlotLine({
                value: data,
                color: "grey",
                width: 2,
                id: 'DDS-Frequency-Indicator',
                dashStyle: 'ShortDash',
                label: {text: data.toString(),
                        verticalAlign: 'bottom',
                        y:-30,
                        style: {color: 'grey'}}
            });
        },
        add_series: function(data, color) {
            var series = {
                data: data,
                color: color,
            };
            var node = this.refs.chartNode;
            $(node).highcharts().addSeries(series);
        },
        get_point: function(index, series) {
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            return chart.series[series].points[index];
        },
        update_tooltip: function(index, series, e) {
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            var point = this.get_point(index, series);
            chart.tooltip.refresh(point);
            chart.xAxis[0].drawCrosshair(e, point);
            chart.yAxis[0].drawCrosshair(e, point);
        },
        hide_tooltip: function() {
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            chart.tooltip.hide(chart.tooltip.hideTimer);
        },
        clear: function() {
            var node = this.refs.chartNode;
            var chart = $(node).highcharts();
            while (chart.series.length)
                chart.series[0].remove(false);
            chart.redraw();
        },
        render: function() {
            return (
                React.DOM.div({className: "chart", ref: "chartNode"})
            );
        }
    });
    var SweepGraphs = React.createClass({
        clear: function() {
            this.refs.amplitude_graph.clear();
            this.refs.phase_graph.clear();
        },
        emit_tooltip: function(index, series, e) {
            this.refs.amplitude_graph.update_tooltip(index, series, e);
            this.refs.phase_graph.update_tooltip(index, series, e);
        },
        emit_tooltip_hide: function() {
            this.refs.amplitude_graph.hide_tooltip();
            this.refs.phase_graph.hide_tooltip();
        },
        handle_click: function(frequency, index, series) {
            if (this.props.advanced == true) {
                sweeper.set_frequency_on_select(frequency);
                var amplitude_graph_point = this.refs.amplitude_graph.get_point(index, series);
                pid.set_setpoint(amplitude_graph_point.y / 2);
            }
        },
        render: function() {
            return (
                <div>
                    <SweepGraph ref="amplitude_graph" title={"Amplitude"} ylabel={"Amplitude (V)"} data_connection={sweeper.new_amplitude_data} DDS_set={dds.stable_frequency_set} emit_tooltip={this.emit_tooltip} emit_tooltip_hide={this.emit_tooltip_hide} handle_click={this.handle_click}/>
                    <SweepGraph ref="phase_graph" title={"Phase"} ylabel={"Phase (degrees)"} data_connection={sweeper.new_phase_data} DDS_set={dds.stable_frequency_set} emit_tooltip={this.emit_tooltip} emit_tooltip_hide={this.emit_tooltip_hide} handle_click={this.handle_click}/>
                </div>
            );
        }
    });
    return SweepGraphs;
});
