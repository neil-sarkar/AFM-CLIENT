define(["react", "jsx!pages/number_input", "jsx!pages/dropdown"], function(React, NumberInput, Dropdown) {
	var PIDEnabledSignal = React.createClass({
		componentDidMount: function() {
			pid.enabled_changed.connect(this.update_value);
		},
		getInitialState: function() {
			return {enabled: false};
		},
		update_value: function(new_state) {
			this.setState({
				enabled: new_state
			});
		},
		render: function() {
			return (
				<div>
					<div> Status: {this.state.enabled ? "Enabled" : "Disabled"}</div>
                                        <button className="pid-enable-button settings-drawer-button"
                                                style={{position: 'relative'}}
                                                onClick={this.state.enabled ? pid.set_disabled : pid.set_enabled}>
                                            {this.state.enabled ? "Disable" : "Enable"}
                                        </button>
				</div>
			);
		}
	});
	var PIDControl = React.createClass({
		render: function() {
			return (
				<div>
                                        <NumberInput value_type="pid" name="Proportional" min={-100} max={100} step={0.01} notify_signal={pid.proportional_changed} get_value={pid.proportional} set_value={pid.set_proportional} />
                                        <NumberInput value_type="pid" name="Integral" min={-100000} max={100000} step={1} notify_signal={pid.integral_changed} get_value={pid.integral} set_value={pid.set_integral} />
                                        <NumberInput value_type="pid" name="Setpoint" min={0} max={26.4} step={0.0001} notify_signal={pid.setpoint_changed} get_value={pid.setpoint} set_value={pid.set_setpoint} />
                                        <Dropdown options_list={[
                                                {text: "Amplitude", cmd_number: 0},
                                                {text: "Phase", cmd_number: 1},
                                            ]}
                                            selection_method={pid.set_phase_modulated}
                                            notify_signal={pid.pm_changed}
                                            get_value={pid.phase_modulated}
                                            title="Tracking Signal"/>
					<PIDEnabledSignal/>

				</div>
			);
		}
	});
	return PIDControl;
});

