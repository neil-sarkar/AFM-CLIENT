define(["react", "jsx!pages/approach_graph", "jsx!pages/z_fine_graph", "jsx!pages/inline_approach_controls"], function(React, ApproachGraph, ZFineGraph, InlineApproachControls) {
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

			// hacky way to allow force curve to take precedence and not have the 
			// streaming commands be queued while the force curve is going
			// window.onblur = function() {
			// 	this.refs.z_fine_graph.stop_streaming();
			// 	this.refs.approach_graph.stop_streaming();
			// }.bind(this);
			// window.onfocus = function() {
			// 	this.refs.z_fine_graph.start_streaming();
			// 	this.refs.approach_graph.start_streaming();
			// }.bind(this);
		},
		handleNewData: function(approacher_state, approacher_adc_read) {
			approacher_state = parseInt(approacher_state);
			this.setState({
				status: approacher_state,
			});
			if (approacher_state == 9) {
				this.setState({
					approach_complete: true
				}, function() {
					pid.set_enabled();
				});
				setTimeout(function() {
					this.refs.z_fine_graph.start_streaming();
					this.refs.approach_graph.start_streaming();
				}.bind(this), 500);
			}
			if (this.state.approach_complete && approacher_state == 1) {
				this.setState({
					approach_complete: false
				});
			}
			this.setState({
				approach_in_progress: (approacher_state !== 0)
			});
		},
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep == false) {
				$('#approach-wrapper').hide();
				this.refs.z_fine_graph.stop_streaming();
				this.refs.approach_graph.stop_streaming();
			} else {
				$('#approach-wrapper').show();
				if (!this.state.approach_in_progress) {
					this.refs.z_fine_graph.start_streaming();
					this.refs.approach_graph.start_streaming();	
				}
			}
		},
		start_approaching : function() {
			this.refs.z_fine_graph.stop_streaming();
			this.refs.approach_graph.stop_streaming();
			approacher.cmd_start_auto_approach();
			pid.set_disabled()
		},
		stop_approaching: function() {
			approacher.cmd_stop_auto_approach();
			this.setState({
				approach_in_progress: false
			});
			var that = this;
			setTimeout(function() {
				that.refs.z_fine_graph.start_streaming();
				that.refs.approach_graph.start_streaming();
			}, 500);
		},
		render: function() {
			return (
				<div className="wrapper" id="approach-wrapper">
					<div className="left-flexbox">
						<ApproachGraph ref="approach_graph" establishDataConnection={approacher.new_data.connect} />
						<div className="approacher-status">
							{status_map[this.state.status]}
							{this.state.approach_complete && <div>Approach complete</div>}
						</div>
						<ZFineGraph ref="z_fine_graph" establishDataConnection={dac_6.value_changed.connect}/>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Sample Approach</div>
						<div className="step-description">
							Press the "Approach" button to begin a raising the sample towards the AFM chip.
							The approach is complete once the amplitude value reaches the desired setpoint.
						</div>
						<button className="action-button" onClick={this.state.approach_in_progress ? this.stop_approaching : this.start_approaching}>{this.state.approach_in_progress ? "Pause" : "Approach"}</button>
						<InlineApproachControls />
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
