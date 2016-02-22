define(["react", "console", "underscore"], function(React, console, _) {
    var NumberInput = React.createClass({
        componentDidMount: function() {
            this.props.notify_signal.connect(this.update_value_from_backend_change);
            var element_id = ('#' + this.compressed_name());
            var component = this;
            $(element_id).keydown(function(e){
                var key = e.which;
                // we should update the value on enter (13), down arrow (40), and up arrow (38)
                if (_.some([13, 40, 38], function(key_code) {return key == key_code;})) {
                    component.send_value_to_backend();
                }
            });
        },
        getInitialState: function() {
            return {
                value: this.validate_input_and_format(this.props.get_value)
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
             return (this.props.value_type + "_" + this.props.name).replace(/ /g,'');
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
            var that = this;
            this.setState({
                value: that.validate_input_and_format(value)
            });
        },
        render_text: function(e) {
            var text_to_render = e.target.value;
            this.setState({
                value: text_to_render
            });
        },
        validate_input_and_format: function(num) {
            console.log(num);
            num = this.round(num).toFixed(this.rounding_factor());
            num = num > this.props.max ? this.props.max : num;
            num = num < this.props.min ? this.props.min : num;
            return num;
        },
        send_value_to_backend: function() {
            var that = this;
            setTimeout( function() {
                var new_value = that.validate_input_and_format(parseFloat(that.refs.input.value));
                that.setState({
                    value: new_value
                });
                that.props.set_value(parseFloat(new_value));
            }, 100); // this is in a settimeout to order to let the input value actually change
        },
        render: function() {
            return (
                <div>
                    <label for={this.props.name}>{this.props.name}: </label>
                    <input type="number" ref="input" 
                                        className="number-input" 
                                        id={this.compressed_name()} 
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