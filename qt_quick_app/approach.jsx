define(["react", "constants", "jsx!pages/approach_graph", "jsx!pages/z_fine_graph", "jsx!pages/inline_approach_controls", "jsx!pages/data_stream_graph"], function(React, Constants, ApproachGraph, ZFineGraph, InlineApproachControls, DataStreamGraph) {
	var status_map = {
		0: "motor idle",
		1: "motor waking up",
		2: "retracting quickly",
		3: "stabilizing",
		4: "pausing for measurement",
		5: "taking initial measurement",
		6: "preparing for approach",
		7: "approaching quickly",
		8: "slowing down",
		9: "approaching slowly",
		10: "reached setpoint",
                11: "disengaging",
                12: "retracting quickly"
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
			approacher.new_state.connect(this.handle_new_data);
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
		handle_new_data: function(approacher_state, approach_complete) {
                        approacher_state = parseInt(approacher_state);
                        var action_in_progress = (approacher_state != 0);
			this.setState({
				status: approacher_state,
			});
                        if (approach_complete && !this.state.approach_complete) {
				this.setState({
					approach_complete: true
				}, function() {
					setTimeout(function() {
                                                pid.set_enabled();
						this.allow_dangerous_user_input();
                                        }.bind(this), 300)
				});
                        } else if (this.state.approach_complete && action_in_progress) {
				this.setState({
					approach_complete: false
				});
			}
			this.setState({
                                approach_in_progress: action_in_progress
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
				this.stop_streaming();
			} else {
				$('#approach-wrapper').show();
				this.refs.z_fine_graph.start_streaming();
				this.refs.approach_graph.start_streaming();
                                this.start_streaming();
			}
		},
		start_streaming: function (argument) {
			var stream_interval_id = setInterval(function() {
				approacher.cmd_get_state();
			}.bind(this), Constants.Approach_Poll_Rate);
			
			this.setState({
				interval_id: stream_interval_id,
			});
		},
		stop_streaming: function() {
			clearInterval(this.state.interval_id);
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
			// this.prevent_dangerous_user_input();
                        motor.cancel_timeout_timer(true);
                        pid.set_disabled();
                        dac_z_offset_fine.set_value(1.5);
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
			this.allow_dangerous_user_input();
			clearInterval(warning_interval);
			$(".motor-status").fadeTo("fast", 1);
		},
                start_disengage: function() {
                        motor.cancel_timeout_timer(true);
                        pid.set_disabled();
                        if(dac_z_offset_fine.value() < 1.5) {
                            dac_z_offset_fine.set_value(1.5);
                        }
                        approacher.cmd_start_disengage();
                        motor_status_opacity = 0.5;
                        warning_interval = setInterval(function () {
                                $(".motor-status").fadeTo("fast", motor_status_opacity, function () {
                                        motor_status_opacity = motor_status_opacity == 0.5 ? 1 : 0.5;
                                });
                        }, 300);
                },
                start_retract_fast: function() {
                        motor.cancel_timeout_timer(true);
                        pid.set_disabled();
                        approacher.cmd_start_retract_fast();
                        motor_status_opacity = 0.5;
                        warning_interval = setInterval(function () {
                                $(".motor-status").fadeTo("fast", motor_status_opacity, function () {
                                        motor_status_opacity = motor_status_opacity == 0.5 ? 1 : 0.5;
                                });
                        }, 300);
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
											data_update_signal={adc_z_1.value_changed}
											prompt_read={adc_z_1.read}
											num_points_displayed={Constants.Approach_Num_Points_Displayed}
                                                                                        plotline_default={pid.setpoint()}
											plotline_update_signal={pid.setpoint_changed}
											poll_rate={Constants.Approach_Poll_Rate}
											max_value={3.3} />

						<DataStreamGraph 	ref="z_fine_graph" 
											dom_id="z-fine-graph" 
											chart_title="Fine Z" 
											data_update_signal={dac_z_offset_fine.value_changed} 
											prompt_read={dac_z_offset_fine.cmd_read_value} 
                                                                                        num_points_displayed={Constants.Z_Fine_Num_Points_Displayed}
											poll_rate={Constants.Z_Fine_Poll_Rate}
											max_value={3.3} />
					</div>
					<div className="right-flexbox">
						<div className="step-name">Sample Approach</div>
						<div className="step-description">
							Click "Approach" to bring the AFM in contact with the sample. The AFM will automatically stop when in contact.
						</div>
						<div className="approacher-status">
							<p className={"motor-status " + motor_status_style}><span className="bold-label">Motor status:</span> {status_map[this.state.status]}</p>
							<p className={"approach-status " + approach_status_style}><span className="bold-label">Approach status:</span> {this.state.approach_complete ? <span>approach complete. Click next.</span> : <span>sample not in contact</span>}</p>
						</div>
						<button className="action-button" id="pause-approach-button" onClick={this.state.approach_in_progress ? this.stop_approaching : this.start_approaching}>{this.state.approach_in_progress ? "Pause" : "Approach"}</button>
                                                <button className="action-button" id="disengage-retract-button" onClick={this.state.approach_complete ? this.start_disengage : this.start_retract_fast}>{this.state.approach_complete ? "Disengage" : "Retract"}</button>
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
