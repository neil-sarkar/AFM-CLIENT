define(["react", "constants", "jsx!pages/approach_graph", "jsx!pages/z_fine_graph", "jsx!pages/inline_approach_controls", "jsx!pages/data_stream_graph"], function(React, Constants, ApproachGraph, ZFineGraph, InlineApproachControls, DataStreamGraph) {
	var status_map = {
		0: "motor idle",
		1: "motor waking up",
		2: "retracting quickly",
		3: "pausing for measurement",
		4: "taking initial measurement",
		5: "preparing for approach",
		6: "approaching quickly",
		7: "slowing down",
		8: "approaching slowly",
		9: "reached setpoint",
	};
	var warning_interval;
	var Approach = React.createClass({
		getInitialState : function() {
			return {
				status: 0,
				approach_complete: false,
				approach_in_progress: false,
				advanced: false
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
					setTimeout(function() {
						pid.set_enabled();
						this.allow_dangerous_user_input();
					}.bind(this), 300);
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
			}, function (argument) {
				if (!this.state.approach_in_progress) {
					clearInterval(warning_interval);
				}
			});
		},
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep === false) {
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
		prevent_dangerous_user_input: function() {
			$(":input").prop("disabled", true);
			$("button").prop("disabled", true);
			$("#pause-approach-button").prop("disabled", false);
		},
		allow_dangerous_user_input: function() {
			$(":input").prop("disabled", false);
			$("button").prop("disabled", false);
		},
		start_approaching : function() {
			this.prevent_dangerous_user_input();
			this.refs.z_fine_graph.stop_streaming();
			this.refs.approach_graph.stop_streaming();
			pid.set_disabled();
			approacher.cmd_start_auto_approach();
			motor_status_opacity = 0.5;
			warning_interval = setInterval(function () {
				$(".motor-status").fadeTo("fast", motor_status_opacity, function () {
					motor_status_opacity = motor_status_opacity == 0.5 ? 1 : 0.5;
				});
			}, 300);
		},
		stop_approaching: function() {
			approacher.cmd_stop_auto_approach();
			this.setState({
				approach_in_progress: false,
				status: 0,
			});
			setTimeout(function() {
				this.refs.z_fine_graph.start_streaming();
				this.refs.approach_graph.start_streaming();
			}.bind(this), 250);
			this.allow_dangerous_user_input();
			clearInterval(warning_interval);
			$(".motor-status").fadeTo("fast", 1);
		},
		toggle_advanced_controls: function () {
			this.setState({
				advanced: !this.state.advanced
			});
		},
		render: function() {
			var motor_status_style = this.state.approach_complete ? "completion-background" : "warning-background";
			var approach_status_style = this.state.approach_complete ? "completion-background" : "warning-background";
			return (
				<div className="wrapper" id="approach-wrapper">
					<div className="left-flexbox">
						<DataStreamGraph 	ref="approach_graph"
											dom_id="approach-graph"
											chart_title="Amplitude"
											data_update_signal={adc_5.value_changed}
											prompt_read={adc_5.read}
											num_points_displayed={Constants.Approach_Num_Points_Displayed}
											plotline_default={pid.setpoint}
											plotline_update_signal={pid.setpoint_changed}
											poll_rate={Constants.Approach_Poll_Rate}
											max_value={2.5} />

						<DataStreamGraph 	ref="z_fine_graph" 
											dom_id="z-fine-graph" 
											chart_title="Fine Z" 
											data_update_signal={dac_6.value_changed} 
											prompt_read={dac_6.cmd_read_value} 
											num_points_displayed={Constants.Approach_Num_Points_Displayed} 
											poll_rate={Constants.Z_Fine_Poll_Rate}
											max_value={3.3} />
					</div>
					<div className="right-flexbox">
						<div className="step-name">Sample Approach</div>
						<div className="step-description">
							Click "Approach" to bring the AFM in contact with the sample.
						</div>
						<div className="approacher-status">
							<p className={"motor-status " + motor_status_style}><span className="bold-label">Motor status:</span> {status_map[this.state.status]}</p>
							<p className={"approach-status " + approach_status_style}><span className="bold-label">Approach status:</span> {this.state.approach_complete ? <span>approach complete</span> : <span>sample not in contact</span>}</p>
						</div>
						<button className="action-button" id="pause-approach-button" onClick={this.state.approach_in_progress ? this.stop_approaching : this.start_approaching}>{this.state.approach_in_progress ? "Pause" : "Approach"}</button>
						<div className="nav-buttons-wrapper">
							<button className="action-button" id="back-button" onClick={this.props.go_to_previous_step}>Back</button>
							<button className="action-button" id="next-button" onClick={this.props.go_to_next_step}>Next</button>
						</div>
						<p className="advanced-controls-toggle" onClick={this.toggle_advanced_controls}><span>{this.state.advanced ? "Hide" : "Show"}</span> Advanced Controls</p>
                        <div className={this.state.advanced ? "visible" : "hidden"}>
                            <InlineApproachControls />
                        </div>
					</div>
				</div>
			);
		},
	});
	return Approach;
});