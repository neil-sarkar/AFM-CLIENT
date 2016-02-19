define(["react"], function(React, Slider) {
	var SpeedSlider = React.createClass({
		getInitialState: function() {
			return {
				slider_position: 1 // start at the slowest 
			};
		},
		getDefaultProps: function() {
			return {
				min: 1,
				max: 4,
				step: 1,
			};
		},
		update_value_from_slider_input: function(e) {
			var slider_input = parseInt(e.target.value);
			var speed;
			var microsteps;
			switch(slider_input) {
				case 4:
					speed = 26300;
					microsteps = 1;
					break;
				case 3:
					speed = 26300;
					microsteps = 3;
					break;
				case 2:
					speed = 23000;
					microsteps = 3;
					break;
				case 1:
					speed = 20000;
					microsteps = 3;
					break;
			}
			if (this.state.slider_position != slider_input) {
				this.setState({
					slider_position: slider_input
				});
				motor.speed = speed;
				motor.microstep = microsteps;
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
										value={this.state.slider_position} 
										onInput={this.update_value_from_slider_input}/>
				</div>
			);
		}
	});
	var MotorControl = React.createClass({
		getInitialState: function() {
			return {
				approach_button_pressed: false,
				retract_button_pressed: false
			}
		},
		componentDidMount: function() {
			var self = this;
			$('.approach-button, .retract-button').mousedown(function() {
				if ($(this).hasClass('approach-button'))
					self.setState({ approach_button_pressed: true });
				else if ($(this).hasClass('retract-button'))
					self.setState({ retract_button_pressed: true });		
			});
			$('.approach-button, .retract-button').mouseup(function() {
				self.setState({
					approach_button_pressed: false,
					retract_button_pressed: false

				})
			});
		},
		approach: function() {
			motor.direction = 1;
			motor.state = 1;
			motor.cmd_single_step();
			var self = this;
			setTimeout(function() {
				if (self.state.approach_button_pressed)
					motor.run_continuous();
			}, 50);
		},
		retract: function() {
			motor.direction = 0;
			motor.state = 1;
			motor.cmd_single_step();
			var self = this;
			setTimeout(function() {
				if (self.state.retract_button_pressed)
					motor.run_continuous();
			}, 50);
		},
		stop_motor: function() {
			motor.cmd_stop_continuous();
		},
		render: function() {
			return (
				<div className="motor-control">
					<SpeedSlider />
					<span className="motor-control-button approach-button" onMouseDown={this.approach} onMouseUp={this.stop_motor}>Approach</span>
					<span className="motor-control-button retract-button" onMouseDown={this.retract} onMouseUp={this.stop_motor}>Retract</span>
				</div>
			);
		}
	});
	return MotorControl;
});

