define(["react", "jsx!pages/scan_heatmap", "jsx!pages/spinner"], function(React, ScanHeatMap, Spinner) {
	var Scan = React.createClass({
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep == false) {
				$('#scan-wrapper').hide();
			} else {
				$('#scan-wrapper').show();
			}
		},
		shouldComponentUpdate :function() {
			return false;
		},
		render: function() {
			return (
				<div className="wrapper" id="scan-wrapper">
					<div className="left-flexbox">
						{ScanHeatMap}
					</div>
					<div className="right-flexbox">
						<div className="step-name">Scan</div>
						<div className="step-description">
						Scanning is so cool.
						</div>
						<button onClick={scanner.start_state_machine}>Scan</button>
						<Spinner />
					</div>
				</div>
				)
		},
	});
	return Scan;
});