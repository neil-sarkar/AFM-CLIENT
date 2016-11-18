 define(["jquery", "react"], function($, React) {
        var message_type_map = {
            0: "Error",
            1: "Warning",
            2: "Info",
        };
        var error_map = {
                0: "Auto approach aborted due to low signal",
                1: "Broken device or no device detected"
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
                        $("#notification-manager-wrapper").css('opacity', 0);
                        window.add_stuff = this.handle_approach_low_signal_error.bind(this);
                        window.add_error = this.emit_error.bind(this);
                },
                message_object: function(a_timestamp, a_message_type, a_message_code, a_timeout) {
                    this.timestamp = a_timestamp;
                    this.message_type = a_message_type;
                    this.message_code = a_message_code;
                    this.timeout = a_timeout;
                },
                render_message: function(message, i) {
                    var message_header_class = "bold-label "+message_type_map[message.message_type]+"-Message";
                    var message_header = "[" + message_type_map[message.message_type] + " " + message.timestamp.split(' ').splice(4,2).join(' ') + "]: ";
                    var message_body = error_map[message.message_code];
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
                    console.log("Pushing new message");
                    var new_messages = this.state.messages.slice();
                    var message_out;
                    if(new_messages.length > this.props.max_num_messages){
                        console.log("Shifting out old message");
                        message_out = new_messages.shift();
                        clearTimeout(message_out.timeout);
                    }
                    console.log("Setting timeout for message duration of " + this.props.message_duration);
                    message.timeout = setTimeout(this.shift_messages, this.props.message_duration);
                    console.log(message);
                    new_messages.push(message);
                    this.setState({messages: new_messages}, this.reveal_messages);
                },
                shift_messages: function() {
                    console.log("Shifting old message");
                    var new_messages = this.state.messages.slice();
                    var message_out = new_messages.shift();
                    if(new_messages.length == 0) {
                        console.log("hiding since no messages left");
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
                    var message = new this.message_object(d.toLocaleString(), 0, 0, null);
                    this.push_messages(message);
                },
                emit_error: function() {
                    approacher.approach_low_signal_error();
                },
        })
        return NotificationManager;
});