define(["react", "jsx!pages/number_input", "jsx!pages/dropdown"], function(React, NumberInput, Dropdown) {
	var InlineSweepControls = React.createClass({
		render: function() {
			return (
				<div>
					<NumberInput value_type="sweep"
								name="Start frequency"
								min={0}
								max={100000}
								step={0.01}
								notify_signal={dds.start_frequency_changed}
								get_value={dds.start_frequency}
								set_value={dds.set_start_frequency} />
					<NumberInput value_type="sweep"
								name="Stop frequency"
								min={0}
								max={100000}
								step={0.01}
								notify_signal={dds.end_frequency_changed}
								get_value={dds.end_frequency}
								set_value={dds.set_end_frequency} />
					<NumberInput value_type="sweep" 
								name="Number of Steps"
								min={0}
								max={300}
								step={0.01}  // does this even have 0.01 resolution?
								notify_signal={dds.step_size_changed} 
								get_value={dds.step_size} 
								set_value={dds.set_step_size} />
				</div>
			)
		}
	});
	return InlineSweepControls
});