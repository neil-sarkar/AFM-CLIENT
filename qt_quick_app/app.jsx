define(["react", "dom", "jsx!pages/progress_bar", "jsx!pages/step_data", "jsx!pages/settings_drawer"], function(React, ReactDOM, ProgressBar, StepData, SettingsDrawer) {
    var App = React.createClass({
        getInitialState: function() {
            return {
                step: 1
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
        go_to_step: function(step_to_jump_to) {
            step_to_jump_to = parseInt(step_to_jump_to); // ensure we're getting ints, not string representations of ints
            this.setState({
              step : step_to_jump_to
            });
        },
        componentDidMount: function() {
            $('.wrapper').hide(); // hide all the steps
            this.refs.step_data.show_first_step();
        },
        render: function() { 
            return (
            <div className="app">
                <ProgressBar step={this.state.step} go_to_step={this.go_to_step} step_list={["Setup", "Sweep", "Approach", "Scan"]}/>
                <StepData ref="step_data" step={this.state.step} go_to_next_step={this.go_to_next_step} go_to_previous_step={this.go_to_previous_step}/>
                <SettingsDrawer/>
            </div>
            )
        }
    });
    ReactDOM.render(<App />, document.getElementById('content'));
});


