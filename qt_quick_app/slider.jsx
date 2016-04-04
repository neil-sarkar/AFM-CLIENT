define(["react"], function(React) {
	var Slider = React.createClass({
		componentDidMount: function() {
			this.props.qt_object.value_changed.connect(this.update_value_from_backend_change);
		},
		getInitialState: function() {
			return {
				value: this.props.qt_object.value
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
			this.setState({
				value: value
			});
		},
		update_value_from_slider_input: function(e) {
			var new_value = e.target.value;
			if (this.state.value != new_value) {
				this.setState({
					value: new_value
				});
				this.props.qt_object.value = new_value; // calls set_value due to Q_PROPERTY
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
	return Slider;
});