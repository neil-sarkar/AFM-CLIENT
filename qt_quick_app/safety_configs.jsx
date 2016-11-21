define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
    var SafetyConfigs = React.createClass({
    getInitialState: function() {
        return {
            check_resistances: true,
        };
    },
    handle_check_resistances_change: function(e) {
        this.setState({check_resistances: e.target.checked}, function() {
            afm.set_check_resistances(this.state.check_resistances);
        });
    },
    render: function() {
        return (
            <div>
                <NumberInput value_type="safety"
                            name="Approach Low Limit (V)"
                            min={0}
                            max={3.3}
                            step={0.01}
                            round={2}
                            notify_signal={approacher.signal_low_limit_changed}
                            get_value={approacher.signal_low_limit}
                            set_value={approacher.set_signal_low_limit} />
                <label className="checkbox"><input type="checkbox" onChange={this.handle_check_resistances_change} checked={this.state.check_resistances}/> Check Resistances</label>
            </div>
            );
        }
    });
    return SafetyConfigs;
});
