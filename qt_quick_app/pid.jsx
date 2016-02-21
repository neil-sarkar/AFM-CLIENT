define(["react"], function(React) {
	var NumberInput = React.createClass({
		componentDidMount: function() {
			this.props.notify_signal.connect(this.update_value_from_backend_change);
		},
		getInitialState: function() {
			var initial_value = this.props.get_value();
			return {
				value: initial_value
			};
		},
		calculate_num_decimal_places: function(num) { // http://stackoverflow.com/questions/10454518/javascript-how-to-retrieve-the-number-of-decimals-of-a-string-number
		  var match = (''+num).match(/(?:\.(\d+))?(?:[eE]([+-]?\d+))?$/);
		  if (!match) { return 0; }
		  return Math.max(
		       0,
		       // Number of digits right of decimal point.
		       (match[1] ? match[1].length : 0)
		       // Adjust for scientific notation.
		       - (match[2] ? +match[2] : 0));
		},
		rounding_factor: function() {
			return this.calculate_num_decimal_places(this.props.step);
		},
		round: function(value) {
			return Math.round(value * Math.pow(10, this.rounding_factor())) / Math.pow(10, this.rounding_factor());
		},
		update_value_from_backend_change: function(value) {
			this.setState({
				value: this.round(value)
			});
		},
		update_value_from_user_input: function(e) {
			var new_value = this.round(parseFloat(e.target.value));
			if (this.state.value != new_value) {
				this.setState({
					value: new_value
				});
				this.props.set_value(new_value);
			}
		},
		render: function() {
			var value_to_display = this.state.value.toFixed(this.calculate_num_decimal_places(this.props.step));
			return (
				<div>
					<label for={this.props.name}>{this.props.name}: </label>
					<input type="number" className="number-input" 
										id={this.props.name} 
										min={this.props.min} 
										max={this.props.max} 
										step={this.props.step} 
										value={value_to_display} 
										onInput={this.update_value_from_user_input}/>
				</div>
			);
		}
	});
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
					<button className="pid-enable-button settings-drawer-button" style={{position: 'relative'}} onClick={this.state.enabled ? pid.set_disabled : pid.set_enabled}>{this.state.enabled ? "Disable" : "Enable"}</button>
				</div>
			);
		}
	});
	var PIDControl = React.createClass({
		render: function() {
			return (
				<div>
					<NumberInput name="Proportional" min={0} max={10000} step={0.001} notify_signal={pid.proportional_changed} get_value={pid.proportional} set_value={pid.set_proportional} />
					<NumberInput name="Integral" min={0} max={10000} step={0.001} notify_signal={pid.integral_changed} get_value={pid.integral} set_value={pid.set_integral} />
					<NumberInput name="Setpoint" min={0} max={2.5} step={0.0001} notify_signal={pid.setpoint_changed} get_value={pid.setpoint} set_value={pid.set_setpoint} />
					<PIDEnabledSignal/>

				</div>
			);
		}
	});
	return PIDControl;
});

