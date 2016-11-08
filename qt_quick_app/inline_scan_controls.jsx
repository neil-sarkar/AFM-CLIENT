define(["react", "jsx!pages/number_input", "jsx!pages/dropdown", "jsx!pages/text_input", "jsx!pages/pga_controller", "jsx!pages/dac_controller", "jsx!pages/scan_range_slider", "jsx!pages/pid"], function(React, NumberInput, Dropdown, TextInput, PGAController, DACController, ScanRangeSlider, PIDControl) {
	var InlineScanControls = React.createClass({
		render: function() {
			return (
                                <div className="top-row">
                                        <div>
                                                <Dropdown options_list={[{text: "Line", cmd_number: 1}, {text: "Area", cmd_number: 4}]}
                                                          selection_method={scanner.set_ratio}
                                                          notify_signal={scanner.ratio_changed}
                                                          get_value={scanner.ratio}
                                                          title="Scan Mode"
                                                          ref = "scan_mode" />
                                                <Dropdown options_list={[{text: "Forward", cmd_number: 'f'}, {text: "Reverse", cmd_number: 'b'}]}
                                                          selection_method={scanner.set_leveling_direction}
                                                          notify_signal={scanner.leveling_direction_changed}
                                                          get_value={scanner.leveling_direction}
                                                          title="Leveling direction" />
                                                <PGAController name="Leveling" qt_object={pga_leveling}/>
                                                <DACController name="Z Coarse" qt_object={dac_z_offset_coarse}/>
                                        </div>
                                        <PIDControl />
				</div>
			)
		}
	});
	return InlineScanControls
});
