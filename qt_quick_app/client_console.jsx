 define(["jquery", "react"], function($, React) {
    var ClientConsole = React.createClass({
        getInitialState: function() {
            return {
                toPrint: []
            };
        },
        componentDidMount: function() {
            // register click handler on open/close button
            $( "#toggle-console" ).on( "click", function() {
                $(this).toggleClass("active");
                if ($(this).hasClass("active")) {
                    $("#client-console-wrapper").css('visibility', 'visible');
                }
                else {
                    $("#client-console-wrapper").css('visibility', 'hidden');
                }
            });

            $("#client-console-wrapper").css('visibility', 'hidden');
            $("#clear-console").on("click",function(){
                 $(".console_message").remove();
            });
            //Connect signals here
            firmware_updater.to_console.connect(this.incoming_message);
        },

        incoming_message: function(message){
            var buffer = this.state.toPrint.slice();
            buffer.push(message);
            this.setState({toPrint: buffer});
        },

        wipe_messages: function (message){
            var blank = [];
            this.setState({toPrint: blank});
        },

        render_message: function(message, i) {
            var text = "";
            return (
                <p key={i} className="console_message">
                    {text + message}
                </p>
                );
        },

        render: function() {
            return (
                <div id="client-console-wrapper">
                    {this.state.toPrint.map(this.render_message)}
                    <p id="clear-console">Clear</p>
                </div>
            );
        }
    })
    return ClientConsole;
});
