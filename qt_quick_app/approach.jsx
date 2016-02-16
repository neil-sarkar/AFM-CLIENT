 define(["react", "jsx!pages/approach_graph"], function(React, Graph) {
	var Approach = React.createClass({
		render: function() {
			return (
				<div className="wrapper">
					<div className="left-flexbox">
						{Graph}
					</div>
					<div className="right-flexbox">
						<div className="step-name">Sample Approach</div>
						<div className="step-description">
							Press the "Approach" button to begin a raising the sample towards the AFM chip.
						</div>
						<button onClick={approacher.cmd_start_auto_approach}>Approach</button>
					</div>
				</div>
			);
		},
	});
	return Approach;
});
