define(["react", "jsx!pages/number_input", "jsx!pages/dropdown", "jsx!pages/text_input", "jsx!pages/pga_controller", "jsx!pages/scan_range_slider"], function(React, NumberInput, Dropdown, TextInput, PGAController, ScanRangeSlider) {
	var InlineScanControls = React.createClass({
		render: function() {
			return (
				<div>
					<Dropdown options_list={[
								{text: "8", cmd_number: 8},
								{text: "16", cmd_number: 16},
								{text: "32", cmd_number: 32},
								{text: "64", cmd_number: 64},
								{text: "128", cmd_number: 128},
								{text: "256", cmd_number: 256},
								{text: "512", cmd_number: 512},
								{text: "1024", cmd_number: 1024},
							]}
							selection_method={scanner.set_num_columns}
							notify_signal={scanner.num_columns_changed}
							title="Number of Columns"/>
					<Dropdown options_list={[
								{text: "8", cmd_number: 8},
								{text: "16", cmd_number: 16},
								{text: "32", cmd_number: 32},
								{text: "64", cmd_number: 64},
								{text: "128", cmd_number: 128},
								{text: "256", cmd_number: 256},
								{text: "512", cmd_number: 512},
								{text: "1024", cmd_number: 1024},
							]}
							selection_method={scanner.set_num_rows}
							notify_signal={scanner.num_rows_changed}
							title="Number of Rows"/>
					<NumberInput value_type="scan" 
								name="Send Back Count"
								min={0}
								max={1024}
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
					<PGAController name="Leveling" qt_object={pga_8}/>
					<ScanRangeSlider name="Scan Range" qt_objects={[pga_1, pga_2, pga_3, pga_4]} />
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