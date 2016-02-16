define(["react", "dom", "jsx!pages/progress_bar", "jsx!pages/step_data", "jsx!pages/settings_drawer"], function(React, ReactDOM, ProgressBar, StepData, SettingsDrawer) {
    var X = React.createClass({
        getInitialState: function() {
            return {
                step: 0
            };
        },
        go_to_next_step: function() {
            this.setState({
              step : this.state.step + 1
            });
        },
        go_to_previous_step: function() {
            this.setState({
              step : this.state.step - 1
            });
        },
        go_to_step: function(step) {
            this.setState({
              step : step
            });
        },
        render: function() {
            return (
                <div>
                    <ProgressBar step={this.state.step} go_to_step={this.go_to_step} />
                    <StepData step={this.state.step} go_to_next_step={this.go_to_next_step} go_to_previous_step={this.go_to_previous_step}/>
                    <SettingsDrawer step={this.state.step} go_to_next_step={this.go_to_next_step} go_to_previous_step={this.go_to_previous_step}/>
                </div>
            )
        }
    });

    ReactDOM.render(<X />, document.getElementById('content'));
    // element = React.createElement(Chart, {container:"chart", options:config});
    // ReactDOM.render(element, document.getElementById('content'));
    // React.render(<ReactHighcharts config = {config}></ReactHighcharts>, document.getElementById('content'));
});


