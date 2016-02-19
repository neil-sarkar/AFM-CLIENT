define(["react"], function(React) {
	var Slider = React.createClass({
		getInitialState: function() {
			return {
				value: this.props.qt_object.value
			};
		},
		getDefaultProps: function() {
			return {
				min: 0,
				max: 100,
				step: 1,
			};
		},
		update_value: function(e) {
			this.setState({
				value: e.target.value
			});
		},
		render: function() {
			return (
				<div className="slider">
					<div>{this.props.name}</div>
					<input type="range" min={this.props.min} 
										max={this.props.max} 
										step={this.props.step} 
										value={this.state.value} 
										onInput={this.update_value}/>
				</div>
			);
		}
	});
	return Slider;
});