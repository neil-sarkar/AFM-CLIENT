define(["react", "jsx!pages/sweep", "jsx!pages/approach", "jsx!pages/scan"], function(React, Sweep, Approach, Scan) {
	var StepData = React.createClass({
		render: function() {
			return (
				<div>
					<Sweep showStep={this.props.step == 0} 
						   go_to_next_step={this.props.go_to_next_step} />
					<Approach showStep={this.props.step == 1} 
						   go_to_next_step={this.props.go_to_next_step} 
						   go_to_previous_step={this.props.go_to_previous_step} />
					<Scan showStep={this.props.step == 2} 
						   go_to_previous_step={this.props.go_to_previous_step}/>
				</div>
			)	
		},
	});
	return StepData;
});