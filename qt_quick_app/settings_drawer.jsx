 define(["jquery", "react", "jsx!pages/slider", "jsx!pages/pga_controller", "jsx!pages/dac_controller", "jsx!pages/adc_controller", "jsx!pages/motor_control", "jsx!pages/pid", "jsx!pages/dds_controller", "jsx!pages/save_folder"], function($, React, Slider, PGAController, DACController, ADCController, MotorControl, PIDControl, DDSControl, SaveFolderPicker) {
	var SettingsDrawer = React.createClass({
		componentDidMount: function() {
			// hide the settings drawer
			// $('#settings-drawer-wrapper').css('visibility', 'hidden');

			// if the user clicks away from the settings drawer, hide it
			// taken from http://stackoverflow.com/questions/1403615/use-jquery-to-hide-a-div-when-the-user-clicks-outside-of-it
                        $(document).mousedown(function (e) {
			    var container = $("#settings-drawer-wrapper");
			    if (!container.is(e.target) // if the target of the click isn't the container...
			        && container.has(e.target).length === 0 // ... nor a descendant of the container
			        && !($('#nav-toggle').is(e.target))) // or we're clicking the close button
			    {
			        container.css('visibility', 'hidden');
			        $('#nav-toggle').removeClass("active");
			    }
			});

			// register click handler on open/close button
			$( "#nav-toggle" ).on( "click", function() {
			    $(this).toggleClass("active");
			    if ($(this).hasClass("active")) {
			    	$("#settings-drawer-wrapper").css('visibility', 'visible');
				} else {
					$("#settings-drawer-wrapper").css('visibility', 'hidden');
				}
			});

			$("#settings-drawer-wrapper").css('visibility', 'hidden');
		},
                render: function() {
				return (
                                            <div id="settings-drawer-wrapper">
                                                    <p className="setting-section-name">Motor Control</p>
                                                    <MotorControl />
                                                    <p className="setting-section-name">PID Control</p>
                                                    <PIDControl />
                                                    <p className="setting-section-name">DACs (/3.3V)</p>
                                                    <div className="settings-container">
                                                            <DACController name="X1" qt_object={dac_x_1}/>
                                                            <DACController name="X2" qt_object={dac_x_2}/>
                                                            <DACController name="Y1" qt_object={dac_y_1}/>
                                                            <DACController name="Y2" qt_object={dac_y_2}/>
                                                            <DACController name="Leveling" qt_object={dac_leveling}/>
                                                            <DACController name="Tip" qt_object={dac_tip}/>
                                                            <DACController name="Z Fine" qt_object={dac_z_offset_fine} slider={true}/>
                                                            <DACController name="Z Coarse" qt_object={dac_z_offset_coarse} slider={true}/>
                                                    </div>
                                                    <p className="setting-section-name">PGAs (/100%)</p>
                                                    <div className="settings-container">
                                                            <PGAController name="X1" qt_object={pga_x_1}/>
                                                            <PGAController name="X2" qt_object={pga_x_2}/>
                                                            <PGAController name="Y1" qt_object={pga_y_1}/>
                                                            <PGAController name="Y2" qt_object={pga_y_2}/>
                                                            <PGAController name="Z Fine" qt_object={pga_fine_z}/>
                                                            <PGAController name="Z Coarse" qt_object={pga_coarse_z}/>
                                                            <PGAController name="DDS" qt_object={pga_dds}/>
                                                            <PGAController name="Leveling" qt_object={pga_leveling}/>
                                                    </div>
                                                    <p className="setting-section-name">ADCs (/3.3V)</p>
                                                    <div className="settings-container">
                                                            <ADCController name="X1" qt_object={adc_x_1}/>
                                                            <ADCController name="X2" qt_object={adc_x_2}/>
                                                            <ADCController name="Y1" qt_object={adc_y_1}/>
                                                            <ADCController name="Y2" qt_object={adc_y_2}/>
                                                            <ADCController name="Z" qt_object={adc_z_1}/>
                                                            <ADCController name="Z Piezo" qt_object={adc_z_piezoresistor_amplitude}/>
                                                            <ADCController name="Phase" qt_object={adc_phase}/>
                                                    </div>
                                                    <button style={{position: 'relative'}} className="settings-drawer-button adc-read-button" onClick={afm.read_all_ADCs}>Read All</button>
                                                    <p className="setting-section-name">Resistances (Ohm)</p>
                                                    <div className="settings-container">
                                                            <ADCController name="X1" qt_object={adc_x_1} resistance={true}/>
                                                            <ADCController name="X2" qt_object={adc_x_2} resistance={true}/>
                                                            <ADCController name="Y1" qt_object={adc_y_1} resistance={true}/>
                                                            <ADCController name="Y2" qt_object={adc_y_2} resistance={true}/>
                                                            <ADCController name="Z" qt_object={adc_z_1} resistance={true}/>
                                                    </div>
                                                    <p className="setting-section-name">DDS (Hz)</p>
                                                    <DDSControl />
                                                    <p className="setting-section-name">Save Options</p>
                                                    <SaveFolderPicker />
                                                    <button style={{position: 'relative'}} className="settings-drawer-button reset-afm-button" onClick={afm.trigger_mcu_reset}>Reset AFM</button>
                                                    <button style={{position: 'relative'}} className="settings-drawer-button get-resistances-button" onClick={afm.cmd_get_resistances}>Reistances</button>
                                                    <button style={{position: 'relative'}} className="settings-drawer-button force-curve-button" onClick={main_window.pop_out_force_curve_page}>Force curve</button>
                                                    <button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" onClick={afm.restore_defaults}>Restore defaults</button>
                                                    <button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" onClick={afm.release_port}>Release Port</button>
                                            </div>
				);
		},
	})
	return SettingsDrawer;
});
