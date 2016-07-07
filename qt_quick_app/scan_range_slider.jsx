define(["react"], function(React) {
    var ScanRangeSlider = React.createClass({
        componentDidMount: function() {
            for (var i = 0; i < this.props.qt_objects.length; i++)
                this.props.qt_objects[i].value_changed.connect(this.update_value_from_backend_change);
            this.props.is_line_changed.connect(this.update_value_from_backend_change);
        },
        getInitialState: function() {
            return {
                value: this.props.qt_objects[0].value()
            };
        },
        getDefaultProps: function() {
            return {
                min: 0,
                max: 196,
                step: 1,
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
        render: function() {
            return (
                <div className="slider">
                    <label htmlFor={this.props.name}>{this.props.name}:</label>
                    <input type="range" id={this.props.name}
                                        min={this.props.min} 
                                        max={this.props.max} 
                                        step={this.props.step} 
                                        value={this.state.value}
                                        onChange={this.update_value_from_slider_input}/>
                    <span>  {Math.round((this.props.is_line() ? 4 : 1)*this.state.value*14/10)/10} um</span>
                </div>
            );
        }
    });
    return ScanRangeSlider;
});
