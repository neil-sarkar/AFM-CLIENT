 define(["jquery", "react", "jsx!pages/slider", "jsx!pages/number_input", "jsx!pages/pga_controller", "jsx!pages/dac_controller"], function($, React, Slider, NumberInput, PGAController, DACController) {
	var SettingsDrawer = React.createClass({
		componentDidMount: function() {
			// hide the settings drawer
			$('#settings-drawer-wrapper').css('visibility', 'hidden');

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
							<p className="setting-section-name">Programmable Gain Amplifiers</p>
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
							<p className="setting-section-name">Digital to Analog Converters</p>
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
								<DACController name="Z Fine" qt_object={dac_6}/>
								<DACController name="Z Coarse" qt_object={dac_8}/>
							</div>
						</div>
					</div>
				);
		},
	})
	return SettingsDrawer;
});