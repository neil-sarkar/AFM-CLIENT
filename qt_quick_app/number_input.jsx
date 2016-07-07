define(["react", "console", "underscore"], function(React, console, _) {
    var NumberInput = React.createClass({
        componentDidMount: function() {
            this.props.notify_signal.connect(this.update_value_from_backend_change);
            $(this.refs.input).keydown(function(e){
                var key = e.which;
                // we should update the value on enter (13), down arrow (40), and up arrow (38)
                if (_.some([13, 40, 38], function(key_code) {return key == key_code;})) {
                    this.send_value_to_backend();
                }
            }.bind(this));
            $(this.refs.input).focusout(function() {
                this.send_value_to_backend();
            }.bind(this));
            this.setState({
                value: this.validate_input_and_format(this.props.get_value())
            });
        },
        getInitialState: function() {
            return {
                value: this.validate_input_and_format(this.props.get_value())
            };
        },
        getDefaultProps: function() {
            return {
                min: 0,
                max: 100,
                step: 1,
            };
        },
        compressed_name: function() {
             return (this.props.value_type + "_" + this.props.name).replace(/[^a-zA-Z0-9-:_]/gi, '');
             // SHOULD TEST  accordance with http://xahlee.info/js/html_allowed_chars_in_attribute.html
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
                value: this.validate_input_and_format(value)
            });
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
            return num.toFixed(this.rounding_factor());
        },
        send_value_to_backend: function() {
            this.props.set_value(parseFloat(this.state.value));
        },
        render: function() {
            return (
                <div>
                    <label htmlFor={this.props.name}>{this.props.name}: </label>
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
