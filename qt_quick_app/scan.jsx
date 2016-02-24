define(["react", "jsx!pages/scan_viewer", "jsx!pages/inline_scan_controls"], function(React, ScanViewer, InlineScanControls) {
	var Scan = React.createClass({
		getInitialState: function() {
			return {
				scanning: false, 
				starting_fresh_scan: true
			};
		},
		componentWillReceiveProps : function(nextProps) {
			if (nextProps.showStep == false) {
				$('#scan-wrapper').hide();
			} else {
				$('#scan-wrapper').show();
			}
		},
		popout: function() {
			console.log("popout");
			main_window.createWindow();
		},
		pause_scanning: function() {
			this.setState({
				scanning: false,
			}, function(){
				scanner.pause_state_machine();
			});
		},
		set_scan_complete: function() {
			this.setState({
				scanning: false,
				starting_fresh_scan: true,
			});
		},
		componentDidMount: function() {
			scanner.all_data_received.connect(this.set_scan_complete);
		},
		// this whole tristate scanning button really should just be done with a dictionary
		start_or_resume_scanning: function() {
			this.setState({
				scanning: true,
			}, function(){
				if (this.state.starting_fresh_scan) {
					this.refs.scan_viewer.clear();
					scanner.start_state_machine();
				} else {
					scanner.resume_state_machine();
				}
				this.setState({
					starting_fresh_scan: false
				});
			});
		},
		clear_scan: function() {
			this.pause_scanning();
			scanner.reset();
			var that = this;
			setTimeout(function() {
				that.refs.scan_viewer.clear();
				that.set_scan_complete();
			}, 200); // give time for the scnaner to actually pause 
			// so data doesn't get rendered 
			// (maybe this should happen on a signal) or have a "accepting data" state check before dispatching
		},
		eliminate_outliers: function() {	
			this.refs.scan_viewer.eliminate_outliers();
		},
		render: function() {
			 // the states will need fixing - clean button should be disabled until scanning completely done (should edit how states work)
			console.log(this.state.scanning, this.state.starting_fresh_scan);
			return (
				<div className="wrapper" id="scan-wrapper">
					<div className="left-flexbox">
						<ScanViewer ref="scan_viewer" establishDataConnection={scanner.new_forward_offset_data.connect} newScan={scanner.started_scan_state_machine.connect}/>
						<button className="action-button" onClick={this.popout}>Popout</button>
					</div>
					<div className="right-flexbox">
						<div className="step-name">Scan</div>
						<div className="step-description">
						Scanning is so cool.
						</div>
						<button className="action-button" onClick={this.state.scanning ? this.pause_scanning : this.start_or_resume_scanning}>{this.state.scanning ? "Pause" : (this.state.starting_fresh_scan ? "Scan" : "Resume")}</button>
						<button className="action-button" onClick={this.clear_scan}>Clear</button>
						<button className="action-button" onClick={this.eliminate_outliers} disabled={this.state.scanning}>Clean</button>
						<button className="action-button" onClick={scanner.save_raw_data} disabled={this.state.scanning}>Download Data</button>
						<InlineScanControls />
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