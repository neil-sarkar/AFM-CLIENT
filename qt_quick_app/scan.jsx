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
						<ScanHeatMap establishDataConnection={scanner.new_forward_offset_data.connect}/>
						<button className="action-button" onClick={this.popout}>Popout</button>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Scan</div>
						<div className="step-description">
						Scanning is so cool.
						</div>
						<button className="action-button" onClick={scanner.start_state_machine}>Scan</button>
						<button className="action-button" onClick={scanner.pause_state_machine}>Pause</button>
						<button className="action-button" onClick={scanner.resume_state_machine}>Resume</button>
						<div className="nav-buttons-wrapper">
							<button className="action-button" id="back-button" onClick={this.props.go_to_previous_step}>Back</button>
						</div>
					</div>
				</div>
				)
		},
	});
	return Scan;
});

// <ScanHeatMap chart_name="Reverse Offset" establishDataConnection={scanner.new_reverse_offset_data.connect} />