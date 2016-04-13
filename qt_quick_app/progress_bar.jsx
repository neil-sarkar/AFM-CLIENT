 define(["react", "classnames"], function(React, classNames) {
	var ProgressBar = React.createClass({
		getDefaultProps: function() {
			return ({
				step_list: []
			});
		},
		render: function() {
			var steps = [];
			for (var step in this.props.step_list) {
                console.log(step, this.props.step);
				steps.push(<ProgressBarStep key={step} name={this.props.step_list[step]} this_step={step} go_to_step={this.props.go_to_step} active={this.props.step == step}/>);
			}
            return (
            	<div>
            		<div className="home-button" onClick={main_window.load_home_page}>Home</div>
            		<div className="progress-bar">{steps}</div>
            		<a id="nav-toggle" href="#"><span></span></a>
            	</div>
            	);
		},
	});

	var ProgressBarStep = React.createClass({
		render: function() {
			var this_step_number = this.props.this_step;
            var active_class = this.props.active ? "active-step" : "";
			return (<span className={"progress-bar-step " + active_class} onClick={this.props.go_to_step.bind(this, this_step_number)}> {this.props.name} </span>);
		}
	})
	return ProgressBar;
});