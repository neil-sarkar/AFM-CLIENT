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
								notify_signal={sweeper.start_frequency_changed}
								get_value={sweeper.start_frequency}
								set_value={sweeper.set_start_frequency} />
					<NumberInput value_type="sweep"
								name="Stop frequency"
								min={0}
								max={100000}
								step={0.01}
								notify_signal={sweeper.end_frequency_changed}
								get_value={sweeper.end_frequency}
								set_value={sweeper.set_end_frequency} />
					<NumberInput value_type="sweep" 
								name="Number of Steps"
								min={0}
								max={300}
								step={0.01}  // does this even have 0.01 resolution?
								notify_signal={sweeper.step_size_changed}
								get_value={sweeper.step_size} 
								set_value={sweeper.set_step_size} />
				</div>
			)
		}
	});
	return InlineSweepControls
});