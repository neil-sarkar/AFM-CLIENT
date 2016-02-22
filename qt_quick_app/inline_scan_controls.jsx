define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
	var InlineScanControls = React.createClass({
		render: function() {
			return (
				<div>
					<NumberInput value_type="scan" 
								name="Number of Points to Average"
								min={0}
								max={255} 
								step={1} 
								notify_signal={scanner.num_averages_changed} 
								get_value={scanner.num_averages} 
								set_value={scanner.set_num_averages} />
					<NumberInput value_type="scan" 
								name="Dwell Time (ms)"
								min={0}
								max={255}
								step={1} 
								notify_signal={scanner.dwell_time_changed} 
								get_value={scanner.dwell_time} 
								set_value={scanner.set_dwell_time} />
				</div>
			)
		}
	});
	return InlineScanControls
});