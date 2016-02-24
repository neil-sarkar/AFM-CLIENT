 define(["jquery", "react", "jsx!pages/slider", "jsx!pages/pga_controller", "jsx!pages/dac_controller", "jsx!pages/adc_controller", "jsx!pages/motor_control", "jsx!pages/pid"], function($, React, Slider, PGAController, DACController, ADCController, MotorControl, PIDControl) {
	var SettingsDrawer = React.createClass({
		componentDidMount: function() {
			// hide the settings drawer
			// $('#settings-drawer-wrapper').css('visibility', 'hidden');

			// if the user clicks away from the settings drawer, hide it
			// taken from http://stackoverflow.com/questions/1403615/use-jquery-to-hide-a-div-when-the-user-clicks-outside-of-it
			$(document).mouseup(function (e) {
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

		},
		render: function() {
			var self = this;
				return (
					<div>
						<div id="settings-drawer-wrapper">
							<p className="setting-section-name">Motor Control</p>
							<MotorControl />
							<p className="setting-section-name">PID Control</p>
							<PIDControl />
							<p className="setting-section-name">PGAs (/100%)</p>
							<div className="settings-container">
								<PGAController name="X1" qt_object={pga_1}/>
								<PGAController name="X2" qt_object={pga_2}/>
								<PGAController name="Y1" qt_object={pga_3}/>
								<PGAController name="Y2" qt_object={pga_4}/>
								<PGAController name="Z Fine" qt_object={pga_5}/>
								<PGAController name="Z Coarse" qt_object={pga_7}/>
								<PGAController name="DDS" qt_object={pga_6}/>
								<PGAController name="Leveling" qt_object={pga_8}/>
							</div>
							<p className="setting-section-name">DACs (/3.3V)</p>
							<div className="settings-container">
								<DACController name="Buffered 1" qt_object={dac_0}/>
								<DACController name="Buffered 2" qt_object={dac_1}/>
								<DACController name="Buffered 3" qt_object={dac_5}/>
								<DACController name="Board 1" qt_object={dac_4}/>
								<DACController name="Board 2" qt_object={dac_2}/>
								<DACController name="Z Amplitude" qt_object={dac_3}/>
								<DACController name="X1" qt_object={dac_10}/>
								<DACController name="X2" qt_object={dac_11}/>
								<DACController name="Y1" qt_object={dac_7}/>
								<DACController name="Y2" qt_object={dac_9}/>
								<DACController name="Z Fine" qt_object={dac_6} slider={true}/>
								<DACController name="Z Coarse" qt_object={dac_8} slider={true}/>
							</div>
							<p className="setting-section-name">ADCs (/2.5V)</p>
							<div className="settings-container">
								<ADCController name="X1" qt_object={adc_3}/>
								<ADCController name="X2" qt_object={adc_7}/>
								<ADCController name="Y1" qt_object={adc_6}/>
								<ADCController name="Y2" qt_object={adc_8}/>
								<ADCController name="Z" qt_object={adc_2}/>
								<ADCController name="Z Piezo" qt_object={adc_5}/>
								<ADCController name="Phase" qt_object={adc_0}/>
							</div>
							<button style={{position: 'relative'}} className="settings-drawer-button adc-read-button" onClick={afm.read_all_ADCs}>Read All</button>
							<br />
							<button style={{position: 'relative'}} className="settings-drawer-button reset-afm-button" onClick={afm.trigger_mcu_reset}>Reset AFM</button>
							<button style={{position: 'relative'}} className="settings-drawer-button get-resistances-button" onClick={afm.cmd_get_resistances}>Reistances</button>
							<button style={{position: 'relative'}} className="settings-drawer-button restore-defaults-button" onClick={afm.restore_defaults}>Restore defaults</button>
						</div>
					</div>
				);
		},
	})
	return SettingsDrawer;
});