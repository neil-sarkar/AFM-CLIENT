define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
	var PGAController = React.createClass({
		render: function() {
			return <NumberInput name={this.props.name} 
								qt_object={this.props.qt_object} 
								min={0}
								max={100}
								step={1} />
		}	
	});
	return PGAController;
});