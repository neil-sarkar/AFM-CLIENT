 define(["react", "jsx!pages/amplitude_graph", "jsx!pages/approach"], function(React, AmplitudePhaseGraph, Approach) {
	var StepData = React.createClass({
		render: function() {
			var step_component;
			switch(this.props.step) {
				case 0:
					step_component = AmplitudePhaseGraph
					break;
				case 1:
					step_component = <Approach />
					break;
				case 2:
					step_component = <Scan />
					break;
			}	
			return (
				<div>
					<button onClick={this.props.go_to_next_step} >Next</button>
					<button onClick={this.props.go_to_previous_step}>Previous</button>		
					{step_component}
				</div>
			)
			
		},
	});
	return StepData;
});