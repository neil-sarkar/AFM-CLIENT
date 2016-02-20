define(["react", "jsx!pages/scan_viewer"], function(React, ScanViewer) {
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
						<ScanViewer establishDataConnection={scanner.new_forward_offset_data.connect} newScan={scanner.started_scan_state_machine.connect}/>
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