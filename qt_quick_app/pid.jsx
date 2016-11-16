define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
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
                                        <NumberInput value_type="pid" name="Proportional" min={0} max={10000} step={0.001} round={3} notify_signal={pid.proportional_changed} get_value={pid.proportional} set_value={pid.set_proportional} />
                                        <NumberInput value_type="pid" name="Integral" min={0} max={10000} step={0.001} round={3} notify_signal={pid.integral_changed} get_value={pid.integral} set_value={pid.set_integral} />
                                        <NumberInput value_type="pid" name="Setpoint" min={0.3} max={3.3} step={0.0001} round={4} notify_signal={pid.setpoint_changed} get_value={pid.setpoint} set_value={pid.set_setpoint} />
					<PIDEnabledSignal/>

				</div>
			);
		}
	});
	return PIDControl;
});

