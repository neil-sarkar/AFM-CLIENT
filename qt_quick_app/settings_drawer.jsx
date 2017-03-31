 define(["jquery", "react", "jsx!pages/slider", "jsx!pages/pga_controller", "jsx!pages/dac_controller", "jsx!pages/adc_controller", "jsx!pages/motor_control", "jsx!pages/pid", "jsx!pages/dds_controller", "jsx!pages/save_folder", "jsx!pages/safety_configs"], function($, React, Slider, PGAController, DACController, ADCController, MotorControl, PIDControl, DDSControl, SaveFolderPicker, SafetyConfigs) {
	var SettingsDrawer = React.createClass({
        getInitialState: function() {
            return {gui_version: afm.get_software_version(),
                    firmware_version: "",
                    server_gui_version: "",
                    mcu_bin: "",
                    setting_is_locked: true,
                    server_firmware_version: "",
                    setting_lock: true};
        },
		componentDidMount: function() {
			// hide the settings drawer
			// $('#settings-drawer-wrapper').css('visibility', 'hidden');

			// if the user clicks away from the settings drawer, hide it
			// taken from http://stackoverflow.com/questions/1403615/use-jquery-to-hide-a-div-when-the-user-clicks-outside-of-it
                        $(document).mousedown(function (e) {
			    var container = $("#settings-drawer-wrapper");
                            var home = $(".home");
			    if (!container.is(e.target) // if the target of the click isn't the container...
			        && container.has(e.target).length === 0 // ... nor a descendant of the container
                                && !home.is(e.target) // if target of click is not home button
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

                        $(".setting-section-name").on("click", function(){
                            $(this).next().slideToggle("fast");
                        });

			$("#settings-drawer-wrapper").css('visibility', 'hidden');

            afm.new_firmware_version.connect(this.handle_new_firmware_version);
            afm.new_server_data.connect(this.handle_new_server_data);
            afm.mcu_bin_changed.connect(this.handle_new_mcu_bin);
            afm.setting_lock_toggled.connect(this.handle_setting_lock_toggle);
            //To handle discrepency between webkit & backend load speed on windows and mac. Check if connection is made first before issuing firmware get.
            var firmware_version = afm.get_firmware_version();
            if(firmware_version)
                this.handle_new_firmware_version(firmware_version);
            this.handle_new_mcu_bin(afm.mcu_bin_file());
            this.handle_setting_lock_toggle(afm.setting_lock());
            afm.contact_server();
		},
        enter_bootloader: function() {
            afm.enter_bootloader();
        },
        update_firmware: function() {
            afm.update_firmware(afm.mcu_bin_file());
        },
        gui_status: function() {
            if(this.state.gui_version && this.state.server_gui_version) {
                if(this.state.gui_version == this.state.server_gui_version) {
                    return (<div>Software Version: {this.state.gui_version} <span style={{color:"green"}}>(up to date)</span></div>);
                } else {
                    return (<div>Software Version: {this.state.gui_version} <span style={{color:"red"}}>(update available)</span></div>);
                }
            } else if (this.state.gui_version) {
                return (<div>Software Version: {this.state.gui_version}</div>)
            } else {
                return (<div>Software Version: x.x.x.x</div>)
            }
        },
        firmware_status: function() {
            if(this.state.firmware_version && this.state.server_firmware_version) {
                if(this.state.firmware_version == this.state.server_firmware_version) {
                    return (<div>Firmware Version: {this.state.firmware_version} <span style={{color:"green"}}>(up to date)</span></div>);
                } else {
                    return (<div>Firmware Version: {this.state.firmware_version} <span style={{color:"red"}}>(update available)</span></div>);
                }
            } else if (this.state.firmware_version) {
                return (<div>Firmware Version: {this.state.firmware_version}</div>)
            } else {
                return (<div>Firmware Version: x.x.x.x</div>)
            }
        },
        handle_new_server_data: function(json_data) {
            this.setState({
                server_gui_version: json_data["versions"]["gui"],
                server_firmware_version: json_data["versions"]["firmware"]
            });
        },
        handle_new_firmware_version: function(version_string) {
            this.setState({
                firmware_version: version_string
            });
        },
        handle_new_mcu_bin: function(mcu_bin_file) {
            this.setState({
                mcu_bin: mcu_bin_file
            });
        },
        //not sure if back end is necessary, considering that this is only ui anyways.  maybe for future?
        handle_setting_lock_toggle: function(isLocked) {
            this.setState({
                setting_is_locked: isLocked
            });
        },
        toggle_setting_lock: function () {
            afm.toggle_setting_lock();
            this.setState({
                setting_lock: afm.setting_lock()
            });
        },
        render: function() {
    		return (
                <div id="settings-drawer-wrapper">
                    <div id="settings-drawer-wrapper-inner">
                        <p className="setting-section-name">Motor Control</p>
                        <MotorControl/>
                        <p className="setting-section-name">PID Control</p>
                        <PIDControl/>
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
                            <div className="val-container">
                            <ADCController name="X1" qt_object={adc_x_1}/>
                            <ADCController name="X2" qt_object={adc_x_2}/>
                            <ADCController name="Y1" qt_object={adc_y_1}/>
                            <ADCController name="Y2" qt_object={adc_y_2}/>
                            <ADCController name="Z" qt_object={adc_z_1}/>
                            <ADCController name="Z Piezo" qt_object={adc_z_piezoresistor_amplitude}/>
                            <ADCController name="Phase" qt_object={adc_phase}/>
                            </div>
                            <button style={{position: 'relative'}} className="settings-drawer-button adc-read-button" onClick={afm.read_all_ADCs}>Read All</button>
                        </div>
                        <p className="setting-section-name">Resistances (Ohm)</p>
                        <div className="settings-container">
                            <div className="val-container">
                            <ADCController name="X1" qt_object={adc_x_1} resistance={true}/>
                            <ADCController name="X2" qt_object={adc_x_2} resistance={true}/>
                            <ADCController name="Y1" qt_object={adc_y_1} resistance={true}/>
                            <ADCController name="Y2" qt_object={adc_y_2} resistance={true}/>
                            <ADCController name="Z" qt_object={adc_z_1} resistance={true}/>
                            </div>
                            <button style={{position: 'relative'}} className="settings-drawer-button get-resistances-button" onClick={afm.cmd_get_resistances}>Resistances</button>
                        </div>
                        <p className="setting-section-name">DDS (Hz)</p>
                        <DDSControl/>
                        <p className="setting-section-name">Safety Configurations</p>
                        <SafetyConfigs/>
                        <p className="setting-section-name">Updates</p>
                        <div className="settings-container">
                            {this.gui_status()}
                            {this.firmware_status()}
                            <button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" onClick={afm.contact_server}>Check Updates</button>
                        </div>
                        <p className="setting-section-name">Advanced</p>
                        <div className="settings-container">
                            <div id="toggle-setting-lock" onClick={this.toggle_setting_lock}><img className="icon-button" src={this.state.setting_lock ? "qrc:/images/lock.png" : "qrc:/images/unlock.png"}></img></div>
                            <button style={{position: 'relative'}} className="settings-drawer-button force-curve-button" onClick={main_window.pop_out_force_curve_page}>Force curve</button>
                            <button style={{position: 'relative'}} className="settings-drawer-button reset-afm-button" disabled={this.state.setting_is_locked} onClick={afm.trigger_mcu_reset}>Reset AFM</button>
                            <button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" disabled={this.state.setting_is_locked} onClick={afm.restore_defaults}>Restore defaults</button>
                            <button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" disabled={this.state.setting_is_locked} onClick={afm.release_port}>Release Port</button>
                            {/*<button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" disabled={this.state.setting_is_locked} onClick={afm.choose_mcu_bin}>Choose Firmware</button>*/}
                            <button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" disabled={this.state.setting_is_locked} onClick={this.enter_bootloader}>Enter Bootloader</button>
                            {/*<button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" disabled={this.state.setting_is_locked} onClick={this.update_firmware}>Update Firmware</button>*/}
                        </div>
                        <div className="pad-div"></div>
                    </div>
                </div>
    		); //these settings drawer bottom buttons suck. Requires restyle and security.
	    }
    })
    return SettingsDrawer;
});
