 define(["react", "jsx!pages/sweep", "jsx!pages/approach", "jsx!pages/scan"], function(React, Sweep, Approach, Scan) {
	var StepData = React.createClass({
		render: function() {
			console.log("rerendering step data", typeof(this.props.step));
			var step_component;
			switch(this.props.step) {
				case 0:
					step_component = <Sweep />
					break;
				case 1:
					step_component = <Approach />;
					break;
				case 2:
					step_component = <Scan />;
					break;
			}
			return (
				<div>
					<Sweep showStep={this.props.step == 0}/>
					<Approach showStep={this.props.step == 1} />
					<Scan showStep={this.props.step == 2} />
					<button onClick={this.props.go_to_previous_step}>Back</button>
					<button onClick={this.props.go_to_next_step}>Next</button>
				</div>
			)	
		},
	});
	return StepData;
});