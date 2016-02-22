define(["react", "console", "underscore"], function(React, console, _) {
    var NumberInput = React.createClass({
        componentDidMount: function() {
            this.props.qt_object.value_changed.connect(this.update_value_from_backend_change);
            var element_id = ('#' + this.compressed_name());
            var component = this;
            $(element_id).keydown(function(e){
                var key = e.which;
                if (_.some([13, 40, 38], function(key_code) {return key == key_code;})) {
                    component.update_value_from_user_input();
                }
            });
        },
        getInitialState: function() {
            return {
                value: this.get_visual_format(this.round(this.props.qt_object.value))
            };
        },
        getDefaultProps: function() {
            return {
                min: 0,
                max: 100,
                step: 1,
                uid: (new Date().getMilliseconds()),
            };
        },
        compressed_name: function() {
             return (this.props.uid + "_" + this.props.name).replace(/ /g,'');
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
        get_visual_format: function(display_value) {
            string_format = display_value.toString();
            if (display_value % 1 === 0 && string_format[string_format.length - 1] != ".")
                return display_value.toString() + ".0";
            return display_value.toString();
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
            num = this.round(num).toFixed(this.rounding_factor());
            num = num > this.props.max ? this.props.max : num;
            num = num < this.props.min ? this.props.min : num;
            return num;
        },
        update_value_from_user_input: function() {
            var that = this;
            setTimeout( function() {
                var new_value = that.validate_input_and_format(parseFloat(that.refs.input.value));
                that.setState({
                    value: new_value
                });
                that.props.qt_object.value = parseFloat(new_value);
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