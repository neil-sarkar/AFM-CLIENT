define(["react"], function(React) {
    var ScanRangeSlider = React.createClass({
        componentDidMount: function() {
            for (var i = 0; i < this.props.qt_objects.length; i++)
                this.props.qt_objects[i].value_changed.connect(this.update_value_from_backend_change);
        },
        getInitialState: function() {
            return {
                value: this.props.qt_objects[0].value
            };
        },
        getDefaultProps: function() {
            return {
                min: 0,
                max: 100,
                step: 1,
            };
        },
        update_value_from_backend_change: function(value) {
            // Get the max of the different values and display that
            var max_value = this.props.qt_objects[0].value;
            for (var i = 1; i < this.props.qt_objects.length; i++) {
                max_value = Math.max(max_value, this.props.qt_objects[i].value);
            }
            
            this.setState({
                value: max_value
            });
        },
        update_value_from_slider_input: function(e) {
            var new_value = e.target.value;
            if (this.state.value != new_value) {
                this.setState({
                    value: new_value
                });
                for (var i = 0; i < this.props.qt_objects.length; i++) {
                    this.props.qt_objects[i].set_value(new_value); // Set all the values to value of the slider
                }
            }
        },
        render: function() {
            return (
                <div className="slider">
                    <label htmlFor={this.props.name}>{this.props.name}: </label>
                    <input type="range" id={this.props.name}
                                        min={this.props.min} 
                                        max={this.props.max} 
                                        step={this.props.step} 
                                        value={this.state.value} 
                                        onInput={this.update_value_from_slider_input}/>
                </div>
            );
        }
    });
    return ScanRangeSlider;
});