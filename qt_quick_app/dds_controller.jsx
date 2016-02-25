define(["react", "jsx!pages/number_input"], function(React, NumberInput) {
    var DDSController = React.createClass({
    render: function() {
        return (
            <div>
                <NumberInput value_type="sweep"
                            name="Start frequency (Hz)"
                            min={0}
                            max={100000}
                            step={1}
                            notify_signal={dds.start_frequency_changed}
                            get_value={dds.start_frequency}
                            set_value={dds.set_start_frequency} />
                <NumberInput value_type="sweep"
                            name="Stop frequency (Hz)"
                            min={0}
                            max={100000}
                            step={1}
                            notify_signal={dds.end_frequency_changed}
                            get_value={dds.end_frequency}
                            set_value={dds.set_end_frequency} />
                <NumberInput value_type="sweep" 
                            name="Step size (Hz)"
                            min={1}
                            max={300}
                            step={1}
                            notify_signal={dds.step_size_changed}
                            get_value={dds.step_size} 
                            set_value={dds.set_step_size} />
            </div>
            );
        }
    });
    return DDSController;
});
