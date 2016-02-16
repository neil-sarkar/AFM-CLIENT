 define(["react", "jsx!pages/sweep", "jsx!pages/approach", "jsx!pages/scan"], function(React, Sweep, Approach, Scan) {
	var StepData = React.createClass({
		render: function() {
			var step_component;
			switch(this.props.step) {
				case 0:
					step_component = <Sweep />
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
					<button onClick={this.props.go_to_next_step}>Next</button>
					<button onClick={this.props.go_to_previous_step}>Back</button>		
					{step_component}
				</div>
			)
			
		},
	});
	return StepData;
});