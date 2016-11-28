define(["react", "jsx!pages/number_input", "jsx!pages/dropdown", "jsx!pages/pga_controller"], function(React, NumberInput, Dropdown, PGAController) {
	var InlineSweepControls = React.createClass({
		getInitialState: function() {
                        return {num_steps: Math.floor(sweeper.calculate_num_steps())};
		},
		componentDidMount: function() {
			sweeper.num_steps_changed.connect(this.update_num_steps);
		},
		update_num_steps: function(value) {
			this.setState({num_steps : Math.floor(value)});
		},
		render: function() {
			return (
                                <div className="top-row">
                                        <div>
                                                <NumberInput value_type="sweep"
                                                                        name="Start frequency (Hz)"
                                                                        min={0}
                                                                        max={100000}
                                                                        step={1}
                                                                        round={0}
                                                                        notify_signal={sweeper.start_frequency_changed}
                                                                        get_value={sweeper.start_frequency}
                                                                        set_value={sweeper.set_start_frequency} />
                                                <NumberInput value_type="sweep"
                                                                        name="Stop frequency (Hz)"
                                                                        min={0}
                                                                        max={100000}
                                                                        step={1}
                                                                        round={0}
                                                                        notify_signal={sweeper.end_frequency_changed}
                                                                        get_value={sweeper.end_frequency}
                                                                        set_value={sweeper.set_end_frequency} />
                                                <NumberInput value_type="sweep"
                                                                        name="Step size (Hz)"
                                                                        min={1}
                                                                        max={300}
                                                                        step={1}
                                                                        round={0}
                                                                        notify_signal={sweeper.step_size_changed}
                                                                        get_value={sweeper.step_size}
                                                                        set_value={sweeper.set_step_size} />
                                                <p style={{marginTop: 0.3}}>Total number of steps in sweep: <span>{this.state.num_steps}</span></p>
                                        </div>
                                        <div>
                                                <PGAController name="Cantilever Drive Amplitude (%)" qt_object={pga_dds}/>
                                        </div>
				</div>
			)
		}
	});
	return InlineSweepControls
});
