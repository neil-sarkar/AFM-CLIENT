 define(["react", "jsx!pages/scan_heatmap"], function(React, ScanHeatMap) {
	var Scan = React.createClass({
		render: function() {
			return (
				<div className="wrapper">
					<div className="left-flexbox">
						{ScanHeatMap}
					</div>
					<div className="right-flexbox">
						<div className="step-name">Scan</div>
						<div className="step-description">
						</div>
						<button>Scan (unimplemented)</button>
					</div>
				</div>
				)
		},
	});
	return Scan;
});