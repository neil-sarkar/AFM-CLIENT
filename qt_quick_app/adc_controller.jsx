define(["react"], function(React) {

	var ADCController = React.createClass({
		componentDidMount: function() {
			if (this.props.resistance)
				this.props.qt_object.new_resistance_value.connect(this.update_value_from_backend);
			else
				this.props.qt_object.value_changed.connect(this.update_value_from_backend);
		},
		update_value_from_backend: function(value) {
			this.setState({value: value.toFixed(4)});
		},
		getInitialState: function() {
			return {
				value: this.props.qt_object.value
			};
		},
		render: function() {
			return (
					<div className="adc-controller">{this.props.name + ": " + this.state.value}</div>
				);
		}
	});
	return ADCController;
});