define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
	var PGAController = React.createClass({
		render: function() {
			return <NumberInput value_type="pga"
								name={this.props.name} 
								qt_object={this.props.qt_object} 
								min={0}
								max={100}
								step={0.1} />
		}	
	});
	return PGAController;
});