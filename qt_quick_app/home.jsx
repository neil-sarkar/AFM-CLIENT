define(["react", "dom"], function(React, ReactDOM) {
    var status_map = [
        {
            enter_condition: afm.disconnected, // this won't do anything for now, 
            // because we never check to see if our connection is still live
            text: "Waiting for serial connection...",
            transition_condition: afm.setting_dac_table,
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
            return {status: 0};
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
        render: function() {
            return (
                <div className="wrapper home-wrapper">
                    <div className="left-flexbox vertically-centered-column">
                        <img id="home-image" src="qrc:/images/afm.jpeg"></img>
                    </div>
                    <div className="right-flexbox vertically-centered-column">
                        <h1>Welcome to nGauge.</h1>
                        <p>{status_map[this.state.status].text}</p>
                        <button className="action-button" onClick={main_window.load_main_app_page}>Enter</button>
                     </div>
                </div>
            )
        }
    });
    ReactDOM.render(<HomePage />, document.getElementById('content'));
});


