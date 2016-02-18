define(["react", "jsx!pages/scan_heatmap"], function(React, ScanHeatMap) {
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
		popout: function() {
			console.log("popout");
			main_window.createWindow();
		},
		render: function() {
			return (
				<div className="wrapper" id="scan-wrapper">
					<div className="left-flexbox">
						<ScanHeatMap chart_name="Forward Offset" establishDataConnection={scanner.new_forward_offset_data.connect} />
						<button onClick={this.popout}>Popout</button>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Scan</div>
						<div className="step-description">
						Scanning is so cool.
						</div>
						<button onClick={scanner.start_state_machine}>Scan</button>
						<div className="nav-buttons-wrapper">
							<button id="back-button" onClick={this.props.go_to_previous_step}>Back</button>
						</div>
					</div>
				</div>
				)
		},
	});
	return Scan;
});

// <ScanHeatMap chart_name="Reverse Offset" establishDataConnection={scanner.new_reverse_offset_data.connect} />