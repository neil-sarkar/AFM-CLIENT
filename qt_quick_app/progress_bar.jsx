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
        render: function() {
            var steps = [];
            for (var step in this.props.step_list) {
                steps.push(<ProgressBarStep key={step} name={this.props.step_list[step]} this_step={step} go_to_step={this.props.go_to_step} active={this.props.step >= step}/>);
            }

            return (
                <div className="progress-bar-wrapper">
                    <div className="home" onClick={main_window.load_home_page}>
                    </div>
                    <ul id="progressbar">
                      {steps}
                    </ul>
                    <a id="nav-toggle" href="#"><span></span></a>
                </div>
            );
        },
    });
    return ProgressBar;
});
