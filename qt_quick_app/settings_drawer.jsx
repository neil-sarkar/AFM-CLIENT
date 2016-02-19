 define(["react", "jsx!pages/slider"], function(React, Slider) {
	var SettingsDrawer = React.createClass({
		getInitialState: function() {
			return {
				visible: true,
			};
		},
		render: function() {
			var self = this;
				return (
					<div id="settings-drawer-wrapper">
						<Slider name="X1" qt_object={pga_1}/>
						<Slider name="X2" qt_object={pga_2}/>
						<Slider name="Y1" qt_object={pga_3}/>
						<Slider name="Y2" qt_object={pga_4}/>
						<Slider name="Z Fine" qt_object={pga_5}/>
						<Slider name="Z Coarse" qt_object={pga_7}/>
						<Slider name="DDS Amplitude" qt_object={pga_6}/>
						<Slider name="Leveling" qt_object={pga_8}/>
					</div>
				);
		},
	})
	return SettingsDrawer;
});