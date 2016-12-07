define(["jquery", "react"], function($, React) {
    var Setup = React.createClass({
        componentWillReceiveProps : function(nextProps) {
            if (nextProps.showStep === false) {
                $('#setup-wrapper').hide();
            } else {
                $('#setup-wrapper').show();
            }
        },
        render: function() {
            return (
                <div className="wrapper" id="setup-wrapper">
                    <div className="setup-step-wrapper">
                        <img src="qrc:/images/chip_load.jpg"></img>
                        <div className="setup-step-desc">Carefully place daughter board onto the stage then secure with thumb screw.</div>
                    </div>
                    <div className="setup-step-wrapper">
                        <img src="qrc:/images/sample_load.jpg"></img>
                        <div className="setup-step-desc">Align the sample underneath the AFM tip.</div>
                    </div>
                    <div className="nav-buttons-wrapper">
                        <button className="action-button" id="next-button" onClick={this.props.go_to_next_step}>Next</button>
                    </div>
                </div>
            )
        },
    });
    return Setup;
});
