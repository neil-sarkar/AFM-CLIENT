define(["jquery", "react", "dom","jsx!pages/sidebar", "jsx!pages/amplitude_graph"], function($, React, ReactDOM, Sidebar, AmplitudePhaseGraph) {
    var X = React.createClass({
        getInitialState: function() {
            return {
                step_number: 1
            };
        },
        updateState: function(num) {
            this.setState({
                step_number: num
            });
        },
        render: function() {
            sweeper.start_state_machine();
            return (<div><button onClick={sweeper.start_state_machine}>Click me</button><Sidebar />{AmplitudePhaseGraph}</div>);
        }
    });

    ReactDOM.render(<X />, document.getElementById('content'));
    // element = React.createElement(Chart, {container:"chart", options:config});
    // ReactDOM.render(element, document.getElementById('content'));
    // React.render(<ReactHighcharts config = {config}></ReactHighcharts>, document.getElementById('content'));
});
