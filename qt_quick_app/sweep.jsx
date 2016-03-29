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
		manual_sweep: function() {
			setTimeout(function() {
				sweeper.start_manual_sweep(); // TODO: probably don't need this settimeout
			}, 200);
		},
		auto_sweep: function() {
			setTimeout(function() {
				sweeper.start_auto_sweep(); // TODO: probably don't need this settimeout
			}, 200);
		},
		clear: function() {
			this.refs.graphs.clear();
		},
		render: function() {
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
							Click and drag on the graphs to zoom in and out.
						</div>
						<div className="top-row">
							<button className="action-button" onClick={this.auto_sweep}>Auto Sweep</button>
							<button className="action-button" onClick={this.manual_sweep}>Manual Sweep</button>
							<button className="action-button" onClick={this.clear}>Clear</button>
						</div>
						<InlineSweepControls/>
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