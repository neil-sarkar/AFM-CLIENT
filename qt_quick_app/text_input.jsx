define(["react", "console", "underscore"], function(React, console, _) {
    var TextInput = React.createClass({
        componentDidMount: function() {
            console.log(this.props.notify_signal);
            this.props.notify_signal.connect(this.update_value_from_backend_change);
        },
        getInitialState: function() {
            return {
                value: this.props.get_value()
            };
        },
        update_value_from_backend_change: function(value) {
            if (value == this.state.value)
                return;
            this.setState({
                value: value
            });
        },
        validate_input_and_format: function(text) {
            return text;
        },
        send_value_to_backend: function(e) {
            var new_value = this.validate_input_and_format(e.target.value);
            this.setState({
                value: new_value
            });
            this.props.set_value(new_value);
        },
        render: function() {
            return (
                <div>
                    <label for={this.props.name}>{this.props.name}: </label>
                    <input type="text" ref="input" 
                                        className="text-input"
                                        value={this.state.value} 
                                        onChange={this.send_value_to_backend}/>
                </div>
            );
        }
    });
    return TextInput;
});