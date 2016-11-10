define(["react", "console", "underscore"], function(React, console, _) {
    var NumberInput = React.createClass({
        componentDidMount: function() {
            this.props.notify_signal.connect(this.update_value_from_backend_change);
            $(this.refs.input).keydown(function(e){
                var key = e.which;
                // we should update the value on enter (13), down arrow (40), and up arrow (38)
                if (key == 13) {
                    this.send_value_to_backend();
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
                        this.setState({value : input_ele.value}, function(){
                            this.send_value_to_backend();
                        });
                    }
                    else
                        this.send_value_to_backend();
                }
            }.bind(this));
            $(this.refs.input).focus(function() {
                this.setState({has_focus: true});
            }.bind(this));
            $(this.refs.input).focusout(function() {
                this.setState({has_focus: false});
                this.send_value_to_backend();
            }.bind(this));
            this.setState({
                value: this.validate_input_and_format(this.props.get_value())
            });
        },
        getInitialState: function() {
            return {
                value: this.validate_input_and_format(this.props.get_value()),
                has_focus: false,
            };
        },
        getDefaultProps: function() {
            return {
                min: 0,
                max: 100,
                step: 1,
                round: 0
            };
        },
        compressed_name: function() {
             return (this.props.value_type + "_" + this.props.name).replace(/[^a-zA-Z0-9-:_]/gi, '');
             // SHOULD TEST  accordance with http://xahlee.info/js/html_allowed_chars_in_attribute.html
        },
        /*calculate_num_decimal_places: function(num) { // http://stackoverflow.com/questions/10454518/javascript-how-to-retrieve-the-number-of-decimals-of-a-string-number
          var match = (''+num).match(/(?:\.(\d+))?(?:[eE]([+-]?\d+))?$/);
          if (!match) { return 0; }
          return Math.max(
               0,
               // Number of digits right of decimal point.
               (match[1] ? match[1].length : 0)
               // Adjust for scientific notation.
               - (match[2] ? +match[2] : 0));
        },*/
        rounding_factor: function() {
            //return this.calculate_num_decimal_places(this.props.step);
            return this.props.round;
        },
        round: function(value) {
            return Math.round(value * Math.pow(10, this.rounding_factor())) / Math.pow(10, this.rounding_factor());
        },
        update_value_from_backend_change: function(value) {
            if (!this.state.has_focus) {
                this.setState({
                    value: this.validate_input_and_format(value)
                });
            }
        },
        render_text: function(e) {
            this.setState({
                value: e.target.value
            });
        },
        validate_input_and_format: function(num) {
            num = this.round(num);
            num = num > this.props.max ? this.props.max : num;
            num = num < this.props.min ? this.props.min : num;
            num = (this.rounding_factor() < 0) ? num : num.toFixed(this.rounding_factor());
            return num;
        },
        send_value_to_backend: function() {
            this.setState({value: this.validate_input_and_format(this.state.value)}, function() {
                this.props.set_value(parseFloat(this.state.value));
            });
        },
        render: function() {
            var label;
            if(this.props.name)
                label = (<label htmlFor={this.props.name}>{this.props.name}: </label>);
            return (
                <div>
                    {label}
                    <input type="number" ref="input" 
                                        className={"number-input " + this.compressed_name()}
                                        min={this.props.min} 
                                        max={this.props.max} 
                                        step={this.props.step}
                                        value={this.state.value} 
                                        onChange={this.render_text}/>
                </div>
            );
        }
    });
    return NumberInput;
});
