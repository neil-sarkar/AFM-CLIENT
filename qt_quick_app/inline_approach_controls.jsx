define(["react", "jsx!pages/motor_control", "jsx!pages/dac_controller", "jsx!pages/pid"], function(React, MotorControl, DACController, PIDControl) {
	var InlineScanControls = React.createClass({
		render: function() {
			return (
				<div className="top-row">
					<MotorControl/>
					<PIDControl />
					<DACController name="Z Coarse" qt_object={dac_8}/>

				</div>
			)
		}
	});
	return InlineScanControls;
});