define(["react", "jsx!pages/approach_graph"], function(React, Graph) {
	var status_map = {
		0: "Motor idle",
		1: "Motor waking up",
		2: "Retracting quickly",
		3: "Pausing for measurement",
		4: "Taking initial measurement",
		5: "Preparing for approach",
		6: "Approaching quickly",
		7: "Slowing down",
		8: "Approaching slowly",
		9: "Reached setpoint",
	};

	var Approach = React.createClass({
		getInitialState : function() {
			return {
				status: 0,
				approach_complete: false,
				approach_in_progress: false,
			};
		},
		componentDidMount: function() {
			approacher.new_data.connect(this.handleNewData);
		},
		handleNewData: function(approacher_state, approacher_adc_read) {
			approacher_state = parseInt(approacher_state);
			this.setState({
				status: approacher_state,
			});
			if (approacher_state == 9) {
				this.setState({
					approach_complete: true
				});
			}
			if (this.state.approach_complete && approacher_state == 1) {
				this.setState({
					approach_complete: false
				});
			}
			this.setState({
				approach_in_progress: (approacher_state !== 0)
			});
			console.log(this.state.status);
		},
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep == false) {
				$('#approach-wrapper').hide();
			} else {
				$('#approach-wrapper').show();
			}
		},
		render: function() {
			return (
				<div className="wrapper" id="approach-wrapper">
					<div className="left-flexbox">
						{Graph}
						<div className="approacher-status">
							{status_map[this.state.status]}
							{this.state.approach_complete && <div>Approach complete</div>}
						</div>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Sample Approach</div>
						<div className="step-description">
							Press the "Approach" button to begin a raising the sample towards the AFM chip.
							The approach is complete once the amplitude value reaches the desired setpoint.
						</div>
						<button className="action-button" onClick={this.state.approach_in_progress ? approacher.cmd_stop_auto_approach : approacher.cmd_start_auto_approach}>{this.state.approach_in_progress ? "Pause" : "Approach"}</button>
						<div className="nav-buttons-wrapper">
							<button className="action-button" id="back-button" onClick={this.props.go_to_previous_step}>Back</button>
							<button className="action-button" id="next-button" onClick={this.props.go_to_next_step}>Next</button>
						</div>
					</div>
				</div>
			);
		},
	});
	return Approach;
});
