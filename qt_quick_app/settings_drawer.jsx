 define(["jquery", "react", "jsx!pages/slider", "jsx!pages/number_input"], function($, React, Slider, NumberInput) {
	var SettingsDrawer = React.createClass({
		componentDidMount: function() {
			// hide the settings
			$('#settings-drawer-wrapper').css('visibility', 'hidden');

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
							<Slider name="X1" qt_object={pga_1}/>
							<Slider name="X2" qt_object={pga_2}/>
							<Slider name="Y1" qt_object={pga_3}/>
							<Slider name="Y2" qt_object={pga_4}/>
							<Slider name="Z Fine" qt_object={pga_5}/>
							<Slider name="Z Coarse" qt_object={pga_7}/>
							<Slider name="DDS Amplitude" qt_object={pga_6}/>
							<Slider name="Leveling" qt_object={pga_8}/>
							<p>Digital to Analog Converters</p>
						</div>
					</div>
				);
		},
	})
	return SettingsDrawer;
});