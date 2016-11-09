define(["react", "jsx!pages/dac_controller", "jsx!pages/pid"], function(React, DACController, PIDControl) {
        var InlineApproachControls = React.createClass({
                render: function() {
                        return (
                                <div className="top-row">
                                        <PIDControl />
                                        <DACController name="Z Coarse" qt_object={dac_z_offset_coarse}/>
                                </div>
                        )
                }
        });
        return InlineApproachControls;
});
