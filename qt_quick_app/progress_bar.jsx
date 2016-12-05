define(["react"], function(React) {
    var ProgressBarStep = React.createClass({
        handle_click: function() {
            this.props.go_to_step(this.props.this_step);
        },
        render: function() {
            var this_step_number = this.props.this_step;
            var active_class = this.props.active ? "active" : "";
            return (
                <li className={active_class} onClick={this.handle_click}> {this.props.name} </li>
            );
        }
    });

    var ProgressBar = React.createClass({
        go_to_setup: function() {
            this.props.go_to_step(0);
        },
        getInitialState: function() {
                return {update_message: ""};
        },
        componentDidMount: function() {
            afm.updatesAvailable.connect(this.updateStatusChanged);
            afm.network_error.connect(this.networkErrorDetected);
            afm.checkUpdates();
        },
        updateStatusChanged: function(result) {
            var message;
            console.log("updateStatusChanged");
            if(result)
                this.setState({update_message: (<span style={{color: "red"}}>nGauge is up to date</span>)});
            else
                this.setState({update_message: (<span style={{color: "red"}}>Updates available! check icspicorp.com</span>)});
        },
        networkErrorDetected: function() {
            console.log("error detected");
            this.setState({update_message: (<span style={{color: "red"}}>Network error</span>)});
        },
        render: function() {
            var steps = [];
            for (var step in this.props.step_list) {
                if(step != 0)
                    steps.push(<ProgressBarStep key={step} name={this.props.step_list[step]} this_step={step} go_to_step={this.props.go_to_step} active={this.props.step >= step}/>);
            }

            return (
                <div className="progress-bar-wrapper">
                    <div className="home" onClick={main_window.load_home_page}>
                    </div>
                    <div id="setup-link" onClick={this.go_to_setup}><img style={{width: "20px"}} src="qrc:/images/wrench_gray.png"></img></div>
                    <ul id="progressbar">
                      {steps}
                    </ul>
                    <div id="update-message">{this.state.update_message}</div>
                    <a id="nav-toggle" href="#"><span></span></a>
                </div>
            );
        },
    });
    return ProgressBar;
});
