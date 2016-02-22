define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
	var InlineScanControls = React.createClass({
		render: function() {
			return (
				<NumberInput value_type="scan" 
							name="Number of Points Averaged"
							min={0}
							max={255} 
							step={1} 
							notify_signal={scanner.num_averages_changed} 
							get_value={scanner.num_averages} 
							set_value={scanner.set_num_averages} />
			)
		}
	});
	return InlineScanControls
});