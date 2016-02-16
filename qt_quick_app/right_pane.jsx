define(["react"], function(React) {
	var LeftPane = React.createClass({
		render: function() {
			return (
				<div class="step-name">{this.props.long_name}</div>
				<div class="step-description">{this.props.description}</div>
				
				)
		};
	});
});