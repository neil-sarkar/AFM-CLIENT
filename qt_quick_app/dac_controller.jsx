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
                var max;
                if (this.props.name == "Z Coarse") {
                        max = 1.0;
                } else {
                        max = 3.3;
                }
		return (
				<div>
					{slider}
					<NumberInput value_type="dac" 
								name={this.props.name} 
								notify_signal={this.props.qt_object.value_changed}
								get_value={this.props.qt_object.value}
								set_value={this.props.qt_object.set_value}
								min={0} 
                                                                max={max}
                                                                step={0.001}
                                                                round={3} />
				</div>
			);
	}
	});
	return DACController;
});
