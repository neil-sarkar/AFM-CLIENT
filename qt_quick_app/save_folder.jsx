define(["react"], function(React) {

	var SaveFolder = React.createClass({
		componentDidMount: function() {
			afm.save_folder_changed.connect(this.update_value_from_backend);
		},
		update_value_from_backend: function(value) {
			this.setState({value: value});
		},
		getInitialState: function() {
			return {
				value: afm.save_folder
			};
		},
		getDefaultProps: function (argument) {
			return {
				compressed: false
			};
		},
		launch_folder_picker: function() {
			afm.launch_folder_picker();
		},
		render: function() {
			return (
				<div>
					<p className="save-directory">Save Directory: {this.state.value == "" ? "Not Selected" : this.state.value}
						<span>
						{(this.props.compressed ? <span onClick={this.launch_folder_picker} className="dropbtn"> | Select &#8594;</span> : <button style={{position: 'relative'}} className="settings-drawer-button folder-picker-button" onClick={this.launch_folder_picker}>Pick folder</button>)}
						</span>
					</p>
				</div>
				);
		}
	});
	return SaveFolder;
});