define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
	var DACController = React.createClass({
	render: function() {
		return <NumberInput name={this.props.name} qt_object={this.props.qt_object}  min={0} max={3.3} step={0.001} /> 
	}
	});
	return DACController;
});