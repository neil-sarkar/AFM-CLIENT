define(["react"], function(React) {
	var NumberInput = React.createClass({
		componentDidMount: function() {
			this.props.qt_object.value_changed.connect(this.update_value_from_backend_change);
		},
		getInitialState: function() {
			return {
				value: this.round(this.props.qt_object.value)
			};
		},
		getDefaultProps: function() {
			return {
				min: 0,
				max: 100,
				step: 1,
			};
		},
		calculate_num_decimal_places: function(num) { // http://stackoverflow.com/questions/10454518/javascript-how-to-retrieve-the-number-of-decimals-of-a-string-number
		  var match = (''+num).match(/(?:\.(\d+))?(?:[eE]([+-]?\d+))?$/);
		  if (!match) { return 0; }
		  return Math.max(
		       0,
		       // Number of digits right of decimal point.
		       (match[1] ? match[1].length : 0)
		       // Adjust for scientific notation.
		       - (match[2] ? +match[2] : 0));
		},
		rounding_factor: function() {
			return this.calculate_num_decimal_places(this.props.step);
		},
		round: function(value) {
			return Math.round(value * Math.pow(10, this.rounding_factor())) / Math.pow(10, this.rounding_factor());
		},
		update_value_from_backend_change: function(value) {
			this.setState({
				value: this.round(this.props.qt_object.value)
			});
		},
		update_value_from_user_input: function(e) {
			var new_value = this.round(parseFloat(e.target.value));
			if (this.state.value != new_value) {
				this.setState({
					value: new_value
				});
				this.props.qt_object.value = new_value; // calls set_value due to Q_PROPERTY
			}
		},
		render: function() {
			return (
				<div className="slider">
					<label for={this.props.name}>{this.props.name}: </label>
					<input type="number" className="number-input" 
										id={this.props.name} 
										min={this.props.min} 
										max={this.props.max} 
										step={this.props.step} 
										value={this.state.value} 
										onInput={this.update_value_from_user_input}/>
				</div>
			);
		}
	});
	return NumberInput;
});