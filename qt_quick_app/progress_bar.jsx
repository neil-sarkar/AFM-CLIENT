 define(["react", "classnames"], function(React, classNames) {
	var ProgressBar = React.createClass({
		getDefaultProps: function() {
			return ({
				step: 0,
				step_list: []
			});
		},
		render: function() {
			var steps = [];
			console.log(this.props.step_list);
			for (var step in this.props.step_list) {
				steps.push(<ProgressBarStep key={step} name={this.props.step_list[step]} this_step={step} go_to_step={this.props.go_to_step}/>);
			}
            return (<div className="progress-bar">{steps}</div>);
		},
	});

	var ProgressBarStep = React.createClass({
		render: function() {
			var this_step_number = this.props.this_step;
			return (<span className={"progress-bar-step"} onClick={this.props.go_to_step.bind(this, this_step_number)}> {this.props.name} </span>);
		}
	})
	return ProgressBar;
});