define(["jquery", "react", "dom","jsx!pages/sidebar"], function($, React, ReactDOM, Sidebar) {
    var HighchartsBar = React.createClass({displayName: 'HighchartsBar',
      renderChart: function() {
            var node = this.refs.chartNode.getDOMNode();
            var dataSeries = this.props.model;
            jQuery(function ($) {
            $(node).highcharts({
                chart: {
                  plotBackgroundColor: '#EFEFEF',
                    height:300,
                    type: 'bar'
                }
                series: dataSeries //..rest of Highcharts code
            });
        });
     
      },
      componentWillReceiveProps: function(nextProps) {
        // we can use this method to see if the component is receiving props
      },
      shouldComponentUpdate: function(nextProps, nextState) {
        return nextProps.model.length > 0; // should we update the component?
      },
      componentDidMount: function() {
        // this method will be invoked when the component is mounted
      },
      componentDidUpdate: function() {
        this.renderChart(); // after the component props are updated, render the chart into the DOM node
      },
      render: function() {
        return (
          React.DOM.div({className: "chart", ref: "chartNode"})
        );
      }
    });


	var X = React.createClass({
		getInitialState: function() {
			return {
				x: 1
			}
		},
		updateState: function(num) {
			console.log("here");
			this.setState({
				x: num
			})
		},
		render: function() {
			var that = this;
			window.setTimeout(function () {
				that.updateState(2);
			}, 2000)
			if (this.state.x == 1)
				return (<div><Sidebar /><div>l</div></div>);
			else
				return (<div></div>);
		}
	});
	x = 1
	ReactDOM.render(<X/>, document.getElementById('content'));
	// element = React.createElement(Chart, {container:"chart", options:config});
	// ReactDOM.render(element, document.getElementById('content'));
	// React.render(<ReactHighcharts config = {config}></ReactHighcharts>, document.getElementById('content'));
});