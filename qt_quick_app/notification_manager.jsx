 define(["jquery", "react"], function($, React) {
        var message_type_map = {
            0: "Error",
            1: "Warning",
            2: "Info",
        };
        var error_map = {
                0: "Auto approach aborted due to low signal",
                1: "Broken device or no device detected",
                2: "Network error when contacting ICSPI server for updates information",
                3: "Amplitude below setpoint - Resweep for new setpoint"
        };
        var info_map = {
                0: "ICSPI update server response =>"
        };
        var NotificationManager = React.createClass({
                getInitialState: function() {
                    return {
                        messages: []
                    };
                },
                getDefaultProps: function() {
                    return {
                        message_duration: 5000,
                        max_num_of_messages: 10
                    };
                },
                componentDidMount: function() {
                        approacher.approach_low_signal_error.connect(this.handle_approach_low_signal_error);
                        afm.no_device_or_broken_device_error.connect(this.handle_no_device_or_broken_device);
                        approacher.approach_below_setpoint.connect(this.handle_approach_below_setpoint);
                        afm.network_error.connect(this.handle_network_error);
                        afm.new_server_message.connect(this.handle_new_server_message);
                        $("#notification-manager-wrapper").css('opacity', 0);
                },
                message_object: function(a_timestamp, a_message_type, a_message_code, a_timeout, a_additional_string) {
                    this.timestamp = a_timestamp;
                    this.message_type = a_message_type;
                    this.message_code = a_message_code;
                    this.timeout = a_timeout;
                    this.additional_string = a_additional_string;
                },
                render_message: function(message, i) {
                    var message_header_class = "bold-label "+message_type_map[message.message_type]+"-Message";
                    var message_header = "[" + message_type_map[message.message_type] + " " + message.timestamp.split(' ').splice(4,2).join(' ') + "]: ";
                    var message_body;
                    switch(message.message_type) {
                        case 0:
                            message_body = error_map[message.message_code];
                            break;
                        case 1:
                            message_body = "";
                            break;
                        case 2:
                            message_body = info_map[message.message_code];
                            break;
                        default:
                            message_body = "";
                    }
                    if(message.additional_string)
                        message_body = message_body + " " + message.additional_string;
                    return (<p key={i}>
                            <span className={message_header_class}>
                                {message_header}
                            </span>
                            {message_body}
                           </p>)
                },
                reveal_messages: function() {
                    //always scroll to bottom when revealing a new message message
                    var wrapper = $("#notification-manager-wrapper")[0];
                    wrapper.scrollTop = wrapper.scrollHeight - wrapper.clientHeight;
                    //reveal wrapper
                    $("#notification-manager-wrapper").fadeTo("fast", 1);
                },
                hide_messages: function() {
                    $("#notification-manager-wrapper").fadeTo("slow", 0);
                },
                push_messages: function(message) {
                    var new_messages = this.state.messages.slice();
                    var message_out;
                    if(new_messages.length > this.props.max_num_messages){
                        message_out = new_messages.shift();
                        clearTimeout(message_out.timeout);
                    }
                    message.timeout = setTimeout(this.shift_messages, this.props.message_duration);
                    new_messages.push(message);
                    this.setState({messages: new_messages}, this.reveal_messages);
                },
                shift_messages: function() {
                    var new_messages = this.state.messages.slice();
                    var message_out = new_messages.shift();
                    if(new_messages.length == 0) {
                        $("#notification-manager-wrapper").fadeTo( "slow", 0, function(){
                            this.setState({messages: new_messages});
                        }.bind(this));
                    }
                    else {
                        this.setState({messages: new_messages});
                    }
                },
                render: function() {
                    return (
                            <div id="notification-manager-wrapper">
                                {this.state.messages.map(this.render_message)}
                            </div>
                    );
                },
                handle_approach_low_signal_error: function() {
                    var d = new Date();
                    // message_type = 0 [Error]
                    // message_code = 0 [Low Signal Error]
                    var message = new this.message_object(d.toLocaleString(), 0, 0, null, null);
                    this.push_messages(message);
                },
                handle_no_device_or_broken_device: function() {
                    var d = new Date();
                    // message_type = 0 [Error]
                    // message_code = 1 [no device or broken device error]
                    var message = new this.message_object(d.toLocaleString(), 0, 1, null, null);
                    this.push_messages(message);
                },
                handle_approach_below_setpoint: function() {
                    var d = new Date();
                    var message = new this.message_object(d.toLocaleString(), 0, 3, null, null);
                    this.push_messages(message);
                },
                handle_network_error: function() {
                    var d = new Date();
                    // message_type = 0 [Error]
                    // message_code = 2 [network error]
                    var message = new this.message_object(d.toLocaleString(), 0, 2, null, null);
                    this.push_messages(message);
                },
                handle_new_server_message: function(message) {
                    var d = new Date();
                    // message_type = 2 [Info]
                    // message_code = 0 [Update server response]
                    var message = new this.message_object(d.toLocaleString(), 2, 0, null, message);
                    this.push_messages(message);
                }
        })
        return NotificationManager;
});
