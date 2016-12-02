define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
    var SafetyConfigs = React.createClass({
    getInitialState: function() {
        return {
            check_resistances: true,
            limit_switch: true,
        };
    },
    componentDidMount: function() {
        motor.limit_switch_enable_changed.connect(this.limit_switch_backend_change);
        afm.check_resistances_changed.connect(this.check_resistances_backend_change);
    },
    handle_check_resistances_change: function() {
        this.setState({check_resistances: !this.state.check_resistances}, function() {
            afm.set_check_resistances(this.state.check_resistances);
        });
    },
    check_resistances_backend_change: function(enable) {
        this.setState({check_resistances: enable});
    },
    handle_limit_switch_change: function() {
        this.setState({limit_switch: !this.state.limit_switch}, function() {
            motor.set_limit_switch_enable(this.state.limit_switch);
        });
    },
    limit_switch_backend_change: function(enable) {
        this.setState({limit_switch: enable});
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
                <div><label className="checkbox" onClick={this.handle_check_resistances_change}>[{this.state.check_resistances ? "✓":"\u00a0\u00a0\u00a0"}] Check Resistances</label></div>
                <div><label className="checkbox" onClick={this.handle_limit_switch_change}>[{this.state.limit_switch ? "✓":"\u00a0\u00a0\u00a0"}]  Limit Switch</label></div>
            </div>
            );
        }
    });
    return SafetyConfigs;
});
