define(["react"], function(React) {
    motor_settings_map = {
        4: {
            speed: 26300,
            microstep: 1,
        },
        3: {
            speed: 26300,
            microstep: 3,
        },
        2: {
            speed: 23000,
            microstep: 3,
        },
        1: {
            speed: 20000,
            microstep: 3,
        },
    };

    var SpeedSlider = React.createClass({
        getInitialState: function() {
            return {
                slider_position: 1,
                speed: 20000,
            };
        },
        getDefaultProps: function() {
            return {
                min: 1,
                max: 4,
                step: 1,
            };
        },
        componentDidMount: function() {
            motor.speed_changed.connect(this.update_value_from_backend_change);
        },
        update_value_from_slider_input: function(e) {
            var slider_input = parseInt(e.target.value);
            var speed = motor_settings_map[slider_input].speed;
            var microstep = motor_settings_map[slider_input].microstep;
            var slider_position = this.calculate_slider_position(speed, microstep);
            this.setState({
                speed: speed,
                slider_position: slider_position,
            }, function() {
                motor.set_microstep(microstep);
                motor.set_speed(speed);
            });
        },
        update_value_from_backend_change: function(speed) {
            slider_position = this.calculate_slider_position(speed, motor.microstep);
            this.setState({
                speed: speed,
                slider_position: slider_position,
            });
        },
        calculate_slider_position: function(speed, microstep) {
            var i = 1;
            for (var property in motor_settings_map) {
                property = parseInt(property);
                if (motor_settings_map.hasOwnProperty(property) && motor_settings_map[property].speed == speed && motor_settings_map[property].microstep == microstep) {
                    return i;
                }
                i += 1;
            }
            return i;
        },
        render: function() {
            // thre is a warning about how we use value instead of defaultValue in the <input> field
            // but the way its done here with "value" is necessary so that all motor slider components are synced
            return (
                <div className="slider">
                    <label htmlFor="speed">Speed</label>
                    <input type="range" id="speed"
                                        min={this.props.min} 
                                        max={this.props.max} 
                                        step={this.props.step} 
                                        value={this.state.slider_position}
                                        onChange={this.update_value_from_slider_input}/>
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
            motor.set_direction(1);
            motor.set_state(1);
            motor.cmd_single_step();
            var self = this;
            setTimeout(function() {
                if (self.state.approach_button_pressed)
                    motor.run_continuous();
            }, 50);
        },
        retract: function() {
            motor.set_direction(0);
            motor.set_state(1);
            motor.cmd_single_step();
            setTimeout(function() {
                if (this.state.retract_button_pressed)
                    motor.run_continuous();
            }.bind(this), 50);
        },
        stop_motor: function() {
            motor.cmd_stop_continuous();
        },
        render: function() {
            return (
                <div className="motor-control">
                    <SpeedSlider />
                    <button className="settings-drawer-button approach-button" onMouseDown={this.approach} onMouseUp={this.stop_motor}>Approach</button>
                    <button className="settings-drawer-button retract-button" onMouseDown={this.retract} onMouseUp={this.stop_motor}>Retract</button>
                </div>
            );
        }
    });
    return MotorControl;
});

