define(["react", "dom"], function(React, ReactDOM) {
    var status_map = [
        {
            enter_condition: afm.disconnected, // this won't do anything for now, 
            // because we never check to see if our connection is still live
            text: "Waiting for serial connection...",
            transition_condition: afm.initializing,
        },
        {
            text: "Initializing hardware...",
            transition_condition: afm.init_complete,
        },
        {
            text: "AFM ready.",
        }
    ];

    var HomePage = React.createClass({
        getInitialState: function() {
            return {status: 0, version: "x.x.x.x"};
        },
        componentDidMount: function() {
            for (var i = 0; i < status_map.length; i++) {
                var bound_advance = this.advance_state.bind(this, i);
                var bound_set = this.set_state.bind(this, i);
                if (typeof status_map[i].transition_condition !== 'undefined')
                    status_map[i].transition_condition.connect(bound_advance);
                if (typeof status_map[i].enter_condition !== 'undefined')
                    status_map[i].enter_condition.connect(bound_set);
            }
            afm.new_firmware_version.connect(this.new_fw_v);
        },
        set_state: function(index) {
            this.setState({
                status: index
            });
        },
        advance_state: function(index) {
            this.setState({
                status: index + 1
            });
        },
        new_fw_v: function(version_string) {
            this.setState({
                version: version_string
            });
        },
        render: function() {
            return (
                <div className="wrapper home-wrapper">
                    <img id="home-image" src="qrc:/images/afm.jpeg"></img>
                    <div className="right-flexbox vertically-centered-column" id="home-right-flexbox">
                        <h1>Welcome to nGauge.</h1>
                        <p>{status_map[this.state.status].text}</p>
                        <p>Firmware Version: {this.state.version}</p>
                        <button className="action-button" id="home-enter-button"s onClick={main_window.load_main_app_page}>Enter</button>
                     </div>
                </div>
            )
        }
    });
    ReactDOM.render(<HomePage />, document.getElementById('content'));
});


