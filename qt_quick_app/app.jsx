define(["jquery", "react", "dom","jsx!pages/sidebar", "jsx!pages/amplitude_graph"], function($, React, ReactDOM, Sidebar, HighchartsBar) {
    var X = React.createClass({
        getInitialState: function() {
            return {
                x: 1
            }
        },
        updateState: function(num) {
            console.log("here");
            this.setState({
                x: num
            })
        },
        render: function() {
            return (<div><Sidebar /><HighchartsBar /></div>);
        }
    });

    ReactDOM.render(<X />, document.getElementById('content'));
    // element = React.createElement(Chart, {container:"chart", options:config});
    // ReactDOM.render(element, document.getElementById('content'));
    // React.render(<ReactHighcharts config = {config}></ReactHighcharts>, document.getElementById('content'));
});
