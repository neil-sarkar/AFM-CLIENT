define(["react"], function(React, Slider) {
	var SpeedSlider = React.createClass({
		getInitialState: function() {
			return {
				speed: motor.speed
			};
		},
		getDefaultProps: function() {
			return {
				min: 20000,
				max: 26300,
				step: 100,
			};
		},
		update_value_from_backend_change: function(value) {
			this.setState({
				speed: value
			});
		},
		update_value_from_slider_input: function(e) {
			var new_value = parseInt(e.target.value);
			if (this.state.value != new_value) {
				this.setState({
					speed: new_value
				});
				motor.speed = new_value; // calls set_speed
			}
		},
		render: function() {
			return (
				<div className="slider">
					<label for="speed">Speed</label>
					<input type="range" id="speed"
										min={this.props.min} 
										max={this.props.max} 
										step={this.props.step} 
										value={this.state.value} 
										onInput={this.update_value_from_slider_input}/>
				</div>
			);
		}
	});
	var MotorControl = React.createClass({
		componentDidMount: function() {
			$('.approach-button, .retract-button').mousedown(function() {
				$(this).data('clicked', true);
			});
			$('.approach-button, .retract-button').mouseup(function() {
				$(this).data('clicked', false);
			});
		},
		approach: function() {
			motor.direction = 1;
			motor.state = 1;
			motor.cmd_single_step();
			setTimeout(function() {
				if ($('.approach-button').data('clicked')) 
					motor.run_continuous();
			}, 100);
		},
		retract: function() {
			motor.direction = 0;
			motor.state = 1;
			motor.cmd_single_step();
			setTimeout(function() {
				if ($('.retract-button').data('clicked'))
					motor.run_continuous();
			}, 100);
		},
		stop_motor: function() {
			motor.cmd_stop_continuous();
		},
		render: function() {
			return (
				<div>
					<SpeedSlider />
					<span className="approach-button" onMouseDown={this.approach} onMouseUp={this.stop_motor}>Approach</span>
					<span className="retract-button" onMouseDown={this.retract} onMouseUp={this.stop_motor}>Retract</span>
				</div>
			);
		}
		// set speed (slider)
		// approach/retract buttons
		// wake up / put to sleep
		// step (button) (pulse step check box)
		// move continuously (button)
	});
	return MotorControl;
});