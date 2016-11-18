define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
    var SafetyConfigs = React.createClass({
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
            </div>
            );
        }
    });
    return SafetyConfigs;
});
