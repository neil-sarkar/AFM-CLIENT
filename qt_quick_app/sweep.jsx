 define(["react", "jsx!pages/sweep_graphs"], function(React, Graphs) {
	var Sweep = React.createClass({
		render: function() {
			return (
				<div>
					<div className="left-pane">
						<button onClick={sweeper.start_state_machine}>Sweep</button>
						{Graphs}
					</div>
					<div className="right-pane">
						<div className="step-name">Frequency Sweep</div>
						<div className="step-description">
							Press the "Sweep" button to begin a frequency sweep. When the graphs are populated, you may select
							a frequency to drive the cantilever. By default, the resonant frequency is chosen.
						</div>
					</div>
				</div>
				)
		},
	});
	return Sweep;
});