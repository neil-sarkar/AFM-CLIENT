define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
    var LineProfile = React.createClass({
        getInitialState: function() {
            return {
                current_series: 0
            };
        },
        renderChart: function() {
            var node = this.refs.lineProfileNode;
            jQuery(function ($) {
                $(node).highcharts({
                    chart: {
                        plotBackgroundColor: '#EFEFEF',
                        height: 200,
                        type: 'line',
                        zoomType: 'x',
                    },
                    title: {
                        text: "Line Profile"
                    },
                    tooltip: { crosshairs: [true, true] },
                    xAxis: {
                        type: 'linear',
                    },
                    yAxis: {
                        title: {
                            text: 'Amplitude (V)'
                        },
                    },
                    legend: {
                        enabled: false
                    },
                    series: [],
                });
            });
        },
        asyncAddPoint: function(y, z) {
            this.state.chart.series[this.state.chart.series.length - 1].addPoint([y, z], false); // add point WITHOUT redrawing or animating
        },
        handleNewDataWrapper: function(data) {
            var self = this;
            setTimeout(function() {self.handleNewData(data);}, 0);
        },
        handleNewData: function(data) {
            var self = this;
            if (self.state.chart.length)
                var prev_series_index = this.state.chart.series.length - 1;
            this.addSeries(); // create a new series
            var new_series_index = this.state.chart.series.length - 1;
            for (var i = 0; i < data.length; i += 3) {
                self.asyncAddPoint(new_series_index, i, data);
            }
            setTimeout(function() {
                self.state.chart.series[self.state.chart.series.length - 2].hide();
                self.state.chart.redraw(false);
            }, 0);
        },
        addSeries: function() {
            var series = {
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
            };
            this.state.chart.addSeries(series);
        },
        erase_data: function(){
            while (this.state.chart.series.length) {
                this.state.chart.series[0].remove(false);
            }
            this.clear_plotlines();
            this.state.chart.redraw();
        },
        redraw: function() {
            this.state.chart.series[this.state.chart.series.length - 2].hide(); // automatically redraws
        },
        select_series_to_display: function(series_index) {
            for (var i = 0; i < this.state.chart.series.length; i++)
                this.state.chart.series[i].hide();
            this.state.chart.series[series_index].show();
        },
        print_series: function() {
            console.log("deprecated method");
        },
        clear_plotlines: function() {
            while (this.state.chart.yAxis[0].plotLinesAndBands.length) {
                this.state.chart.yAxis[0].removePlotLine('upper');
                this.state.chart.yAxis[0].removePlotLine('lower');
            }
        },
        draw_outlier_plotlines: function(lower, upper) {
            this.clear_plotlines();
            this.state.chart.yAxis[0].addPlotLine({
                value: lower,
                color: 'red',
                dashStyle: 'dash',
                width: 2,
                id: 'upper'
            });
            this.state.chart.yAxis[0].addPlotLine({
                value: upper,
                color: 'red',
                dashStyle: 'dash',
                width: 2,
                id: 'upper'
            });
        },
        componentDidMount: function() {
            this.renderChart();
            // this.props.establishDataConnection(this.handleNewDataWrapper);
            // this.props.newScan(this.erase_data);
            var node = this.refs.lineProfileNode;
            var chart = $(node).highcharts();
            this.setState({
                chart: chart,
            });
            $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug
        },
        render: function() {
            return (React.DOM.div({className: "chart profile", ref: "lineProfileNode"}));
        }
    });
    return LineProfile;
});
