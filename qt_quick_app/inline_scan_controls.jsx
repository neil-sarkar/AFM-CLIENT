define(["react", "jsx!pages/number_input", "jsx!pages/dropdown", "jsx!pages/text_input"], function(React, NumberInput, Dropdown, TextInput) {
	var InlineScanControls = React.createClass({
		render: function() {
			return (
				<div>
					<NumberInput value_type="scan"
								name="Number of Rows" // we map number of rows to num_columns because something seems backwards...
								min={0}
								max={256}
								step={1}
								notify_signal={scanner.num_columns_changed}
								get_value={scanner.num_columns}
								set_value={scanner.set_num_columns} />
					<NumberInput value_type="scan"
								name="Number of Columns"
								min={0}
								max={256}
								step={1}
								notify_signal={scanner.num_rows_changed}
								get_value={scanner.num_rows}
								set_value={scanner.set_num_rows} />
					<NumberInput value_type="scan" 
								name="Send Back Count"
								min={0}
								max={256}
								step={1} 
								notify_signal={scanner.send_back_count_changed} 
								get_value={scanner.send_back_count} 
								set_value={scanner.set_send_back_count} />
					<NumberInput value_type="scan"
								name="Number of Points to Average"
								min={0}
								max={255} 
								step={1} 
								notify_signal={scanner.num_averages_changed} 
								get_value={scanner.num_averages} 
								set_value={scanner.set_num_averages} />
					<NumberInput value_type="scan" 
								name="Dwell Time (ms)"
								min={0}
								max={255}
								step={1} 
								notify_signal={scanner.dwell_time_changed} 
								get_value={scanner.dwell_time} 
								set_value={scanner.set_dwell_time} />
					<NumberInput value_type="scan" 
								name="Remove outliers farther than N RMS"
								min={0}
								max={100}
								step={0.01} 
								notify_signal={scanner.rms_threshold_changed} 
								get_value={scanner.rms_threshold} 
								set_value={scanner.set_rms_threshold} />
					<Dropdown options_list={[{text: "0:1", cmd_number: 1}, {text: "1:1", cmd_number: 2}, {text: "3:1", cmd_number: 4}, {text: "7:1", cmd_number: 8}]} selection_method={scanner.set_ratio} notify_signal={scanner.ratio_changed} title="Scan ratio"/>
					<Dropdown options_list={[{text: "Forward", cmd_number: 'f'}, {text: "Reverse", cmd_number: 'b'}]} selection_method={scanner.set_leveling_direction} notify_signal={scanner.leveling_direction_changed} title="Leveling direction" />
					<TextInput name="File name base" 
								notify_signal={scanner.base_file_name_changed}
								get_value={scanner.base_file_name}
								set_value={scanner.set_base_file_name} />
				</div>
			)
		}
	});
	return InlineScanControls
});