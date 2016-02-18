 define(["jquery" ,"react", "jsx!pages/sweep_graphs"], function($, React, Graphs) {
	var Sweep = React.createClass({	
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep == false) {
				$('#sweep-wrapper').hide();
			} else {
				$('#sweep-wrapper').show();
			}
		},
		shouldComponentUpdate :function() {
			return false;
		},
		render: function() {
			console.log('rendering');
			return (
				<div className="wrapper" id="sweep-wrapper">
					<div className="left-flexbox">
						{Graphs}
					</div>
					<div className="right-flexbox">
						<div className="step-name">Frequency Sweep</div>
						<div className="step-description">
							Press the "Sweep" button to begin a frequency sweep. When the graphs are populated, you may select
							a frequency to drive the cantilever. By default, the resonant frequency is chosen.
						</div>
						<button onClick={sweeper.start_state_machine}>Sweep</button>
					</div>
				</div>
				)
		},
	});
	return Sweep;
});