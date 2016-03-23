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
                        width: 600,
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
        addSeries: function(name) {
            var series = {
                type: "line",
                name: name
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
        set_data: function(forward_data, reverse_data) {
            if (this.state.chart.series.length === 0) {
                this.addSeries("Forward");
                this.addSeries("Reverse");
            }
            this.state.chart.series[0].setData(forward_data.reverse());
            this.state.chart.series[1].setData(reverse_data);
        },
        componentDidMount: function() {
            this.renderChart();
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
