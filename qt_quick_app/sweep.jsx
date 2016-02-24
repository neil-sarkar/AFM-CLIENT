 define(["jquery" ,"react", "jsx!pages/sweep_graphs", "jsx!pages/inline_sweep_controls"], function($, React, Graphs, InlineSweepControls) {
	var Sweep = React.createClass({	
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep == false) {
				$('#sweep-wrapper').hide();
			} else {
				$('#sweep-wrapper').show();
			}
		},
		shouldComponentUpdate : function() {
			return false;
		},
		start_sweep: function() {
			this.refs.graph.clear();
			scanner.reset();
			setTimeout(function() {
				scanner.start_state_machine();	
			}, 200);
		},
		render: function() {
			console.log('rendering');
			return (
				<div className="wrapper" id="sweep-wrapper">
					<div className="left-flexbox">
						<Graphs ref='graphs'/>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Frequency Sweep</div>
						<div className="step-description">
							Press the "Sweep" button to begin a frequency sweep. When the graphs are populated, you may select
							a frequency to drive the cantilever. By default, the resonant frequency is chosen.
						</div>
						<button className="action-button" onClick={sweeper.start_state_machine}>Auto Sweep</button>
						<button className="action-button" onClick={sweeper.start_state_machine}>Manual Sweep</button>
						<InlineSweepControls>
						<div className="nav-buttons-wrapper">
							<button className="action-button" id="next-button" onClick={this.props.go_to_next_step}>Next</button>
						</div>
					</div>
				</div>
				)
		},
	});
	return Sweep;
});