define(["react", "jsx!pages/sweep", "jsx!pages/approach", "jsx!pages/scan"], function(React, Sweep, Approach, Scan) {
	var StepData = React.createClass({
		render: function() {
			var step_component;
			switch(this.props.step) {
				case 0:
					step_component = <Sweep />
					break;
				case 1:
					step_component = <Approach />;
					break;
				case 2:
					step_component = <Scan />;
					break;
			}
			var scan_views = [
			{
				title: "Forward Offset",
				id: "forward_offset",
				data_connection: scanner.new_forward_offset_data
			},
			{
				title: "Reverse Offset",
				id: "reverse_offset",
				data_connection: scanner.new_reverse_offset_data
			},
			{
				title: "Forward Amplitude",
				id: "forward_amplitude",
				data_connection: scanner.new_forward_offset_data
			},
			{
				title: "Reverse Amplitude",
				id: "reverse_amplitude",
				data_connection: scanner.new_reverse_offset_data
			},
			{
				title: "Forward Error",
				id: "forward_amplitude",
				data_connection: scanner.new_forward_offset_data
			},
			{
				title: "Reverse Error",
				id: "reverse_amplitude",
				data_connection: scanner.new_reverse_offset_data
			},
			];
			return (
				<div>
					<Sweep showStep={this.props.step == 0} 
						   go_to_next_step={this.props.go_to_next_step} />
					<Approach showStep={this.props.step == 1} 
						   go_to_next_step={this.props.go_to_next_step} 
						   go_to_previous_step={this.props.go_to_previous_step} />
					<Scan showStep={this.props.step == 2} 
						   go_to_previous_step={this.props.go_to_previous_step} scan_views={scan_views}/>
				</div>
			)	
		},
	});
	return StepData;
});