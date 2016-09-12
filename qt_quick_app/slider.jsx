define(["react"], function(React) {
	var Slider = React.createClass({
		componentDidMount: function() {
			this.props.qt_object.value_changed.connect(this.update_value_from_backend_change);
            $(document).mouseup(function() {
                if(this.state.dragging) {
                    this.setState({dragging: false});
                }
            });
		},
		getInitialState: function() {
			return {
                value: this.props.qt_object.value(),
                dragging: false
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
            if (!this.state.dragging) {
                this.setState({
                    value: value
                });
            }
		},
		update_value_from_slider_input: function(e) {
			var new_value = e.target.value;
			if (this.state.value != new_value) {
				this.setState({
					value: new_value
				});
                this.props.qt_object.set_value(new_value);
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
                                        onMouseDown={function(){ this.setState({dragging: true}); }}
                                        onChange={this.update_value_from_slider_input}/>
				</div>
			);
		}
	});
	return Slider;
});
