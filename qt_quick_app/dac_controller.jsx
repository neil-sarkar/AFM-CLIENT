define(["react", "jsx!pages/number_input", "jsx!pages/slider"], function(React, NumberInput, Slider) {
	var DACController = React.createClass({
	getDefaultProps: function() {
		return {
			slider: false
		};
	},
	render: function() {
		var slider;
		if (this.props.slider) {
			slider = <Slider name={this.props.name} qt_object={this.props.qt_object} min={0} max={3.3} step={0.001} />;
		} else {
			slider = false;
		}
		return (
				<div>
					{slider}
					<NumberInput name={this.props.name} qt_object={this.props.qt_object}  min={0} max={3.3} step={0.001} /> 
				</div>
			);
	}
	});
	return DACController;
});