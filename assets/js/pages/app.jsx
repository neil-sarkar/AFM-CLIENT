define(["jquery", "react", "dom","jsx!pages/sidebar", "highcharts", "jsx!pages/react-native-bootstrap-slider"], function($, React, ReactDOM, Sidebar, highcharts, SliderNativeBootstrap) {
 //    var HighchartsBar = React.createClass({displayName: 'HighchartsBar',
 //      renderChart: function() {
 //            var node = this.refs.chartNode.getDOMNode();
 //            var dataSeries = this.state.model;
 //            console.log("render", dataSeries);
 //            jQuery(function ($) {
 //            $(node).highcharts({
 //                chart: {
 //                  plotBackgroundColor: '#EFEFEF',
 //                    height:300,
 //                    type: 'line'
 //                },
 //                title: { 
 //                	text: 'Amplitude' 
 //                },
 //                tooltip: { crosshairs: [true, true] },
 //                xAxis: {
 //                    type: 'linear',
 //                    title: { text: "Frequency (Hz)" },
 //                },
 //                yAxis: {
 //                    title: {
 //                        text: 'Amplitude (V)'
 //                    },
 //                },
 //                legend: {
 //                    enabled: false
 //                },
 //                series: [
 //                {
	//         	    name: name,
	//         	    data: dataSeries,
	//         	    type: "area",
	//         	    plotOptions: {
	//         	        area: {
	//         	            fillColor: {
	//         	                linearGradient: {
	//         	                    x1: 0,
	//         	                    y1: 0,
	//         	                    x2: 0,
	//         	                    y2: 1
	//         	                },
	//         	                stops: [
	//         	                    [0, Highcharts.getOptions().colors[0]],
	//         	                    [1, Highcharts.Color(Highcharts.getOptions().colors[0]).setOpacity(0).get('rgba')]
	//         	                ]
	//         	            },
	//         	            marker: {
	//         	                radius: 2
	//         	            },
	//         	            lineWidth: 1,
	//         	            states: {
	//         	                hover: {
	//         	                    lineWidth: 1
	//         	                }
	//         	            },
	//         	            threshold: null
	//         	        }
	//         	    },
 //                }
 //                ],
 //                plotOptions: {
 //                   series: {
 //                       point: {
 //                           events: {
 //                               mouseOver: function () {
 //                               }
 //                           }
 //                       },
 //                    }
 //                }
 //            });
 //        });
     	
 //      },
 //      componentWillReceiveProps: function(nextProps) {
 //        // we can use this method to see if the component is receiving props
 //        this.renderChart();
 //      },
 //      getInitialState: function() {
 //      	return {
 //      		model: [[1,1],[2,2]]
 //      	};
 //      },
 //      shouldComponentUpdate: function(nextProps, nextState) {
 //        return nextProps.model.length > 0; // should we update the component?
 //      },
 //      componentDidMount: function() {
 //        this.renderChart();
 //      },
 //      componentDidUpdate: function() {
 //        this.renderChart(); // after the component props are updated, render the chart into the DOM node
 //      },
 //      addSeries: function() {
 //      	var series = {
 //            data: [[3,3],[4,4],[5,5]],
 //            type: "area",
 //            plotOptions: {
 //                area: {
 //                    fillColor: {
 //                        linearGradient: {
 //                            x1: 0,
 //                            y1: 0,
 //                            x2: 0,
 //                            y2: 1
 //                        },
 //                        stops: [
 //                            [0, Highcharts.getOptions().colors[0]],
 //                            [1, Highcharts.Color(Highcharts.getOptions().colors[0]).setOpacity(0).get('rgba')]
 //                        ]
 //                    },
 //                    marker: {
 //                        radius: 2
 //                    },
 //                    lineWidth: 1,
 //                    states: {
 //                        hover: {
 //                            lineWidth: 1
 //                        }
 //                    },
 //                    threshold: null
 //                }
 //            },
 //        }
 //      	var node = this.refs.chartNode.getDOMNode();
 //      	$(node).highcharts().addSeries(series);
 //      },
 //      render: function() {
 //      	var that = this;
 //      	window.setTimeout( function() {
 //      		that.addSeries();
 //      	}, 2000);
 //        return (
 //          React.DOM.div({className: "chart", ref: "chartNode"})
 //        );
 //      }
 //    });


	// var X = React.createClass({
	// 	getInitialState: function() {
	// 		return {
	// 			x: 1
	// 		}
	// 	},
	// 	updateState: function(num) {
	// 		console.log("here");
	// 		this.setState({
	// 			x: num
	// 		})
	// 	},
	// 	render: function() {
	// 		var that = this;
	// 		window.setTimeout(function () {
	// 			that.updateState(2);
	// 			console.log("here");
	// 		}, 2000)
	// 		return (<div><Sidebar /><div>l</div></div>);
	// 	}
	// });

	// ReactDOM.render(<X />, document.getElementById('content'));
	// // element = React.createElement(Chart, {container:"chart", options:config});
	// // ReactDOM.render(element, document.getElementById('content'));
	// // React.render(<ReactHighcharts config = {config}></ReactHighcharts>, document.getElementById('content'));

  var Demo = React.createClass({
      getInitialState: function (){
          return {
              currentValue: this.props.startValue,
              min: this.props.min,
              max: this.props.max,
              step: this.props.step
          };
      },
      render: function() {
          var newValue = this.state.currentValue;
          // TODO: Replace this with bootstrap version
          return (
              <div>
                  <SliderNativeBootstrap
                      value={this.state.currentValue}
                      handleChange={this.changeValue}
                      step={this.state.step}
                      max={this.state.max}
                      min={this.state.min} />
                  <br /><br />
                  Value: {newValue}

                  <br /><br />
                  <button onClick={this.changeAxes}>Change axes!</button>
              </div>
              );
      },
      changeValue: function(e) {
          console.log("changeValue");
          this.setState({currentValue: e.target.value});
      },
      changeAxes: function (){
          this.setState({
              currentValue: 500,
              min: 0,
              max: 2000,
              step: 100
          });
      }
  });
  var a = 3000;
  var b = 20000;
  var c = 1000;
  var d = 1000;
  ReactDOM.render(<Demo startValue={a} max={b} min={c} step={d} />, document.getElementById("content"));
  // ReactDOM.render(<SliderNativeBootstrap
  //                     value={this.state.currentValue}
  //                     handleChange={this.changeValue}
  //                     step={this.state.step}
  //                     max={this.state.max}
  //                     min={this.state.min} />, document.getElementById("content"));

});