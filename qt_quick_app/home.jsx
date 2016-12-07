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
            return {status: 0,
                    gui_version: afm.get_software_version(),
                    firmware_version: "",
                    server_gui_version: "",
                    server_firmware_version: ""};
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
            afm.new_firmware_version.connect(this.handle_new_firmware_version);
            afm.new_server_data.connect(this.handle_new_server_data);
            //afm.cmd_get_firmware_version();
            //afm.contact_server();
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
        handle_new_firmware_version: function(version_string) {
            this.setState({
                firmware_version: version_string
            });
        },
        handle_new_server_data: function(json_data) {
            console.log("new server data");
            window.json_data = json_data;
            this.setState({
                server_gui_version: json_data["versions"]["gui"],
                server_firmware_version: json_data["versions"]["firmware"]
            });
        },
        render: function() {
            return (
                <div className="wrapper home-wrapper">
                    <img id="home-image" src="qrc:/images/afm.jpeg"></img>
                    <div className="right-flexbox vertically-centered-column" id="home-right-flexbox">
                        <h1>Welcome to nGauge.</h1>
                        <p>{status_map[this.state.status].text}</p>
                        <button className="action-button" id="home-enter-button"s onClick={main_window.load_main_app_page}>Enter</button>
                        {this.gui_status()}
                        {this.firmware_status()}
                     </div>
                </div>
            )
        }
    });
    ReactDOM.render(<HomePage />, document.getElementById('content'));
});


