 define(["jquery", "react", "jsx!pages/slider", "jsx!pages/number_input"], function($, React, Slider, NumberInput) {
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