define(["jquery", "react", "dom", "highcharts", "console"], function($, React, ReactDOM, highcharts, console) {
	var AmplitudePhaseGraph = React.createClass({
	    renderChart: function() {
	    	var component = this;
	        var node = this.refs.chartNode.getDOMNode();
	        var siblings = $(node).siblings(); // these are the graphs with which we want to sync our tooltip and zoom
	        var dataSeries = this.state.model;
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
	            series: [
	            {
	                name: name,
	                data: dataSeries,
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
	    		}
	            ],
	            plotOptions: {
	               	series: {
	                 	point: {
	                      	events: {
								mouseOver: function (e) {
									// sync the tooltips of all sibling graphs
									var chart = this.series.chart;
									var index = this.index;
									var series = this.series._i;
									for (var i = 0; i < siblings.length; i += 1) {
										var chart = $(siblings[i]).highcharts();
										var point = chart.series[series].points[index];
										chart.tooltip.refresh(point);
										chart.xAxis[0].drawCrosshair(e, point);
										chart.yAxis[0].drawCrosshair(e, point);
									}
								}
	                       }
	                   },
	                }
	            }
	        });
	    });
	    },
	    componentWillReceiveProps: function(nextProps) {
	    // we can use this method to see if the component is receiving props
	        this.renderChart();
	    },
	    getInitialState: function() {
	        return {
	            model: [[1,1],[2,2], [3,3], [4,4], [5,5]]
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
	    	chart.xAxis[0].setExtremes(min_x - 300, max_x + 300);
	    },
	    addSeries: function(data) {
		    var series = {
		    	data: data,
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
	        var node = this.refs.chartNode.getDOMNode();
	        $(node).highcharts().addSeries(series);
	    },
	    render: function() {
	        return (
	         React.DOM.div({className: "chart", ref: "chartNode"})
	        );
	    }
	});
	return (<div><AmplitudePhaseGraph title={"Amplitude"} establishDataConnection={sweeper.new_amplitude_data.connect}/>
		<AmplitudePhaseGraph title={"Phase"} establishDataConnection={sweeper.new_phase_data.connect}/>
		</div>)
});