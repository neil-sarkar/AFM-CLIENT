define(["react", "jsx!pages/number_input", "jsx!pages/dropdown"], function(React, NumberInput, Dropdown) {
	var InlineSweepControls = React.createClass({
		getInitialState: function() {
			return {num_steps: 0};
		},
		componentDidMount: function() {
			sweeper.num_steps_changed.connect(this.update_num_steps);
		},
		update_num_steps: function(value) {
			this.setState({num_steps : Math.floor(value)});
		},
		render: function() {
			return (
				<div>
					<NumberInput value_type="sweep"
								name="Start frequency"
								min={0}
								max={100000}
								step={1}
								notify_signal={sweeper.start_frequency_changed}
								get_value={sweeper.start_frequency}
								set_value={sweeper.set_start_frequency} />
					<NumberInput value_type="sweep"
								name="Stop frequency"
								min={0}
								max={100000}
								step={1}
								notify_signal={sweeper.end_frequency_changed}
								get_value={sweeper.end_frequency}
								set_value={sweeper.set_end_frequency} />
					<NumberInput value_type="sweep" 
								name="Step size"
								min={1}
								max={300}
								step={1}
								notify_signal={sweeper.step_size_changed}
								get_value={sweeper.step_size} 
								set_value={sweeper.set_step_size} />
					<p style={{marginTop: 0.3}}>Total number of steps in sweep: <span>{this.state.num_steps}</span></p>
				</div>
			)
		}
	});
	return InlineSweepControls
});