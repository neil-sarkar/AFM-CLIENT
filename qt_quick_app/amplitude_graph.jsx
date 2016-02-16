define(["jquery", "react", "dom", "highcharts"], function($, React, ReactDOM, highcharts) {
	var AmplitudePhaseGraph = React.createClass({
	    renderChart: function() {
	    	var component = this;
	        var node = this.refs.chartNode.getDOMNode();
	        var dataSeries = this.state.model;
	        jQuery(function ($) {
	        $(node).highcharts({
	            chart: {
	              	plotBackgroundColor: '#EFEFEF',
	                height: 300,
	                type: 'line'
	            },
	            title: {
	                text: component.props.title
	            },
	            tooltip: { crosshairs: [true, true] },
	            xAxis: {
	                type: 'linear',
	                title: { text: "Frequency (Hz)" },
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
								mouseOver: function () {}
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
	            model: [[1,1],[2,2]]
	        };
	    },
	    shouldComponentUpdate: function(nextProps, nextState) {
	        return nextProps.model.length > 0; // should we update the component?
	    },
	    componentDidMount: function() {
	        this.renderChart();
	        // this.props.establishDataConnection(this.addSeries);
	        $('text:contains("Highcharts.com")').hide(); // remove the annoying marketing plug

	    },
	    componentDidUpdate: function() {
	        this.renderChart(); // after the component props are updated, render the chart into the DOM node
	    },
	    addSeries: function() {
	   	console.log("here");
	    var series = {
	        data: [[3,3],[4,4],[5,5]],
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
	console.log(sweeper);
	return (<div><AmplitudePhaseGraph title={"Amplitude"} establishDataConnection={sweeper.new_amplitude_data.connect}/>
		// <AmplitudePhaseGraph title={"Phase"} />
		</div>)
});