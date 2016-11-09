 define(["jquery" ,"react", "jsx!pages/sweep_graphs", "jsx!pages/inline_sweep_controls"], function($, React, SweepGraphs, InlineSweepControls) {
	var Sweep = React.createClass({
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep === false) {
				$('#sweep-wrapper').hide();
			} else {
				$('#sweep-wrapper').show();
			}
		},
		componentDidMount: function () {
			sweeper.machine_finished.connect(this.on_sweep_done);
		},
		getInitialState: function () {
			return {
				advanced: false,
				can_continue: false,
                                is_sweeping: false,
			};
		},
		on_sweep_done: function () {
			this.setState({
				can_continue: true,
                                is_sweeping: false,
			});
		},
		manual_sweep: function() {
                        this.setState({
                                is_sweeping: true,
                        });
                        pid.set_disabled();
                        dac_z_offset_fine.set_value(1.5);
			setTimeout(function() {
				sweeper.start_manual_sweep(); // TODO: probably don't need this settimeout
			}, 200);
		},
		auto_sweep: function() {
                        this.setState({
                                is_sweeping: true,
                        });
			this.clear();
                        pid.set_disabled();
                        dac_z_offset_fine.set_value(1.5);
			setTimeout(function() {
				sweeper.start_auto_sweep(); // TODO: probably don't need this settimeout
			}, 200);
		},
		clear: function() {
			this.refs.graphs.clear();
		},
		toggle_advanced_controls: function () {
			this.setState({
				advanced: !this.state.advanced,
			});
		},
		render: function() {
			return (
				<div className="wrapper" id="sweep-wrapper">
					<div className="left-flexbox">
						<SweepGraphs ref='graphs' advanced={this.state.advanced}/>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Frequency Sweep</div>
						<div className="step-description">
							Click "Sweep" to find the resonant frequency of the AFM.
						</div>
						<div className="top-row">
                                                        <button className="action-button" onClick={this.auto_sweep} disabled={this.state.is_sweeping}>{this.state.is_sweeping? "Sweeping":"Sweep"}</button>
						</div>
						<p className="advanced-controls-toggle" onClick={this.toggle_advanced_controls}><span>{this.state.advanced ? "Hide" : "Show"}</span> Advanced Controls</p>
						<div className={this.state.advanced ? "visible" : "hidden"}>
							<p>
							 After sweeping, click on the graph to manually select an operating frequency from the curve.
							 By default, the resonant frequency is chosen.
							 Click and drag on the graphs to zoom in and out.
							</p>
							<div className="top-row">
                                                                <button className="action-button" onClick={this.manual_sweep} disabled={this.state.is_sweeping}>Manual Sweep</button>
								<button className="action-button" onClick={this.clear}>Clear</button>
							</div>
							<InlineSweepControls/>
						</div>
					</div>
				</div>
				)
		},
	});
	return Sweep;
});
