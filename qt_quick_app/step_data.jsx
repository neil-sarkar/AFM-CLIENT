define(["react", "jsx!pages/setup", "jsx!pages/sweep", "jsx!pages/approach", "jsx!pages/scan", "jsx!pages/null_step"], function(React, Setup, Sweep, Approach, Scan, NullStep) {
	var StepData = React.createClass({
		show_first_step: function() {
			$('#first_step').show();
		},
		render: function() {
			return (
				<div>
					<Setup ref="first_step" showStep={this.props.step == 0} 
						   go_to_next_step={this.props.go_to_next_step} />
					<Sweep 	showStep={this.props.step == 1} 
							go_to_next_step={this.props.go_to_next_step}
						   	go_to_previous_step={this.props.go_to_previous_step} />
					<Approach showStep={this.props.step == 2} 
						   	go_to_next_step={this.props.go_to_next_step} 
						   	go_to_previous_step={this.props.go_to_previous_step} />
					<Scan showStep={this.props.step == 3} 
							go_to_next_step={this.props.go_to_next_step} 
						   	go_to_previous_step={this.props.go_to_previous_step}/>
					<NullStep showStep={this.props.step == 4} 
						   	go_to_previous_step={this.props.go_to_previous_step} />
				</div>
			)	
		},
	});
	return StepData;
});