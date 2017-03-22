define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
    var PGAController = React.createClass({
        render: function() {
            return <NumberInput value_type="pga"
                name={this.props.name}
                notify_signal={this.props.qt_object.value_changed}
                get_value={this.props.qt_object.value}
                set_value={this.props.qt_object.set_value}
                min={0}
                max={140}
                step={0.1}
                round={1} />
        }
    });
    return PGAController;
});
