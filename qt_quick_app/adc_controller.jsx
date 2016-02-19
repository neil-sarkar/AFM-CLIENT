define(["react", "jsx!pages/number_input", "jsx!pages/slider"], function(React, NumberInput, Slider) {

	var ADCController = React.createClass({
		componentDidMount: function() {
			this.props.qt_object.value_changed.connect(this.update_value_from_backend);
			// this.props.qt_object.read();
		},
		update_value_from_backend: function(value) {
			this.setState({
				value: value
			});
		},
		bits_to_volts: function(value) {
			return (value / 4095 * 2.5).toFixed(2);
		},
		getInitialState: function() {
			return {
				value: this.props.qt_object.value
			};
		},
		render: function() {
			return (
					<div className="adc-controller">{this.props.name + ": " + this.bits_to_volts(this.state.value)} <span className="adc-read-button" onClick={this.props.qt_object.read}>(Read)</span></div>
				);
		}
	});
	return ADCController;
});