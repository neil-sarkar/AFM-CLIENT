define(["react"], function(React) {
    var ScanRangeSlider = React.createClass({
        componentDidMount: function() {
            for (var i = 0; i < this.props.qt_objects.length; i++)
                this.props.qt_objects[i].value_changed.connect(this.update_value_from_backend_change);
            this.props.is_line_changed.connect(this.update_value_from_backend_change);

            $(this.refs.input).keydown(function(e){
                var key = e.which;
                // we should update the value on enter (13), down arrow (40), and up arrow (38)
                if (key == 13) {
                    this.send_number_value_to_backend();
                    $(this.refs.input).blur();
                }
                if (key == 40 || key == 38) {
                    input_ele = $(this.refs.input)[0];
                    if(input_ele.value.indexOf(".") == input_ele.value.lastIndexOf(".")){
                        e.preventDefault();
                        sel_pos = Math.min(input_ele.selectionStart,input_ele.selectionEnd);
                        sep_pos = input_ele.value.indexOf(".");
                        power = sel_pos;
                        if((sep_pos > -1) && (sel_pos <= (sep_pos + 1)))
                            power += 1;
                        if((sel_pos == 0) && (sep_pos != 0))
                            power += 1;
                        power = input_ele.value.length - power;
                        if( key == 38 )
                            input_ele.stepUp(parseInt(Math.pow(10,power)));
                        else
                            input_ele.stepDown(parseInt(Math.pow(10,power)));
                        input_ele.setSelectionRange(sel_pos,sel_pos);
                        this.setState({number_value : input_ele.value}, function(){
                            this.send_number_value_to_backend();
                        });
                    }
                    else
                        this.send_number_value_to_backend();
                }
            }.bind(this));
            $(this.refs.input).focus(function() {
                this.setState({has_focus: true});
            }.bind(this));
            $(this.refs.input).focusout(function() {
                this.setState({has_focus: false});
                this.send_number_value_to_backend();
            }.bind(this));
            $(this.refs.slider).keydown(function(e){
                var key = e.which;
                if (key == 40 || key == 38) {
                    this.update_value_from_slider_input(e);
                }
            }.bind(this));
        },
        getInitialState: function() {
            return {
                value: this.props.qt_objects[0].value(),
                number_value: this.validate_input_and_format(this.pga_to_um(this.props.qt_objects[0].value())),
                has_focus: false
            };
        },
        getDefaultProps: function() {
            return {
                min: 0,
                max: 143, /*196,*/
                step: 1,
                number_step: 0.1,
                round: 1,
                is_line: function(){ return false; }
            };
        },
        update_value_from_backend_change: function() {
            // Get the max of the different values and display that
            var max_value = this.props.qt_objects[0].value();
            for (var i = 1; i < this.props.qt_objects.length; i++) {
                max_value = Math.max(max_value, this.props.qt_objects[i].value());
            }
            
            this.setState({
                value: max_value * max_value / 100
            });

            if (!this.state.has_focus) {
                this.setState({
                    number_value: this.validate_input_and_format(this.pga_to_um(max_value * max_value / 100))
                });
            }
        },
        update_value_from_slider_input: function(e) {
            var new_value = e.target.value;
            if (this.state.value != new_value) {
                this.setState({
                    value: new_value
                });
                for (var i = 0; i < this.props.qt_objects.length; i++) {
                    // Set all the values to value of the slider
                    // Use sqrt in order to linearize the scale
                    this.props.qt_objects[i].set_value(Math.sqrt(new_value*100));
                }
            }
        },
        pga_to_um: function(pag_value) {
            return Math.round((this.props.is_line() ? 4 : 1)*pag_value*14/10)/10;
        },
        um_to_pga: function(um_value) {
            return Math.round(10*10/14/(this.props.is_line() ? 4 : 1)*um_value);
        },
        rounding_factor: function() {
            return this.props.round;
        },
        round: function(value) {
            return Math.round(value * Math.pow(10, this.rounding_factor())) / Math.pow(10, this.rounding_factor());
        },
        validate_input_and_format: function(num) {
            num = this.round(num);
            num = num > this.pga_to_um(this.props.max) ? this.pga_to_um(this.props.max) : num;
            num = num < this.pga_to_um(this.props.min) ? this.pga_to_um(this.props.min) : num;
            num = (this.rounding_factor() < 0) ? num : num.toFixed(this.rounding_factor());
            return num;
        },
        send_number_value_to_backend: function() {
            this.setState({number_value: this.validate_input_and_format(this.state.number_value)}, function() {
                var new_value = this.um_to_pga(this.state.number_value);
                if (this.state.value != new_value) {
                    for (var i = 0; i < this.props.qt_objects.length; i++) {
                        // Set all the values to value of the slider
                        // Use sqrt in order to linearize the scale
                        this.props.qt_objects[i].set_value(Math.sqrt(new_value*100));
                    }
                }
            });
        },
        render_text: function(e) {
            this.setState({
                number_value: e.target.value
            });
        },
        render: function() {
            return (
                <div className="slider">
                    <label htmlFor={this.props.name}>{this.props.name}:</label>
                    <input type="range" ref="slider"
                                        id={this.props.name}
                                        min={this.props.min} 
                                        max={this.props.max} 
                                        step={this.props.step} 
                                        value={this.state.value}
                                        onChange={this.update_value_from_slider_input}/>
                    <input type="number" ref="input"
                                        className={"number-input slider-number"}
                                        id={this.props.name}
                                        min={this.pga_to_um(this.props.min)}
                                        max={this.pga_to_um(this.props.max)}
                                        step={this.props.number_step}
                                        value={this.state.number_value}
                                        onChange={this.render_text}/>
                    <span>um</span>
                </div>
            );
        }
    });
    return ScanRangeSlider;
});
