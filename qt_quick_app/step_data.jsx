define(["react", "jsx!pages/setup", "jsx!pages/sweep", "jsx!pages/approach", "jsx!pages/scan", "jsx!pages/null_step"], function(React, Setup, Sweep, Approach, Scan, NullStep) {
	var StepData = React.createClass({
		show_first_step: function() {
                    this.refs.first_step.componentWillReceiveProps(this.refs.first_step.props);
		},
		render: function() {
			return (
                                <div id="step-data">
                                        <Setup showStep={this.props.step == 0}
						   go_to_next_step={this.props.go_to_next_step} />
                                        <Sweep ref="first_step"	showStep={this.props.step == 1}
							go_to_next_step={this.props.go_to_next_step}
						   	go_to_previous_step={this.props.go_to_previous_step} />
					<Approach showStep={this.props.step == 2} 
						   	go_to_next_step={this.props.go_to_next_step} 
						   	go_to_previous_step={this.props.go_to_previous_step} />
					<Scan showStep={this.props.step == 3} 
							go_to_next_step={this.props.go_to_next_step} 
						   	go_to_previous_step={this.props.go_to_previous_step}/>
				</div>
                        )
		},
	});
	return StepData;
});
