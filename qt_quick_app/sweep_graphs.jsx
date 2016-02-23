define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var SweepGraph = React.createClass({
        renderChart: function() {
            var component = this;
            var node = this.refs.chartNode.getDOMNode();
            var siblings = $(node).siblings(); // these are the graphs with which we want to sync our tooltip and zoom
            var dataSeries = this.state.model;
            var series = this.generate_initial_series();
            console.log("rendering chart", series);
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                    plotBackgroundColor: '#EFEFEF',
                    height: 300,
                    type: 'line',
                    zoomType: 'x',
                },
                title: {
                    text: component.props.title
                },
                tooltip: { crosshairs: [true, true] },
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
                        text: 'Amplitude (V)'
                    },
                },
                legend: {
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
                                    component.props.emit_tooltip(index, series, e);
                                },
                                click: function(e) {
                                    component.props.handle_click(e.point.x, this.index, this.series._i); // capture the y value
                                },
                           }
                       },
                    }
                }
            });
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
        componentWillReceiveProps: function(nextProps) {
        // we can use this method to see if the component is receiving props
            this.renderChart();
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
            return nextProps.model.length > 0; // should we update the component?
        },
        componentDidMount: function() {
            this.renderChart();
            this.props.establishDataConnection(this.handleNewData);
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        componentDidUpdate: function() {
            this.renderChart(); // after the component props are updated, render the chart into the DOM node
        },
        handleNewData: function(data) {
            var two_dimensional_data = [];
            var min_x = 100000;
            var max_x = 0;
            for (i = 0; i < data.length; i += 2) {
                min_x = data[i] < min_x  ? data[i] : min_x;
                max_x = data[i] > max_x  ? data[i] : max_x;
                two_dimensional_data.push([data[i], data[i+1]]);
            }
            this.addSeries(two_dimensional_data);
            this.state.model.push([]);
            (this.state.model[this.state.model.length - 1]).push(two_dimensional_data);
            var node = this.refs.chartNode.getDOMNode();
            $(node).highcharts().xAxis[0].setExtremes(min_x - this.props.zoom_buffer, max_x + this.props.zoom_buffer);
        },
        addSeries: function(data) {
                var series = {
                    data: data,
                };
            var node = this.refs.chartNode.getDOMNode();
            $(node).highcharts().addSeries(series);
        },
        get_point: function(index, series) {
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            return chart.series[series].points[index];
        },
        update_tooltip: function(index, series, e) {
            var node = this.refs.chartNode.getDOMNode();
            var chart = $(node).highcharts();
            var point = this.get_point(index, series);
            chart.tooltip.refresh(point);
            chart.xAxis[0].drawCrosshair(e, point);
            chart.yAxis[0].drawCrosshair(e, point);
        },
        clear: function() {
            var node = this.refs.chartNode.getDOMNode();
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
            this.refs.pahse_graph.clear();
        },
        emit_tooltip: function(index, series, e) {
            this.refs.amplitude_graph.update_tooltip(index, series, e);
            this.refs.phase_graph.update_tooltip(index, series, e);
        },
        handle_click: function(frequency, index, series) {
            sweeper.set_frequency_on_select(frequency);
            var amplitude_graph_point = this.refs.amplitude_graph.get_point(index, series);
            pid.set_setpoint(amplitude_graph_point.y / 2);
        },
        render: function() {
            return (
                <div>
                    <SweepGraph ref="amplitude_graph" title={"Amplitude"} establishDataConnection={sweeper.new_amplitude_data.connect} emit_tooltip={this.emit_tooltip} handle_click={this.handle_click}/>
                    <SweepGraph ref="phase_graph" title={"Phase"} establishDataConnection={sweeper.new_phase_data.connect} emit_tooltip={this.emit_tooltip} handle_click={this.handle_click}/>
                </div>
            );
        }
    });
    return SweepGraphs;
});
