define(["react", "dom"], function(React, ReactDOM) {
    var HomePage = React.createClass({
        render: function() {
            return (
                <div className="home-wrapper">
                    <img id="home-image" src="qrc:/images/afm.jpeg"></img>
                    <div className="column-container">
                        <h1 id="welcome-text">Welcome to openAFM.</h1>
                        <p>Checking...</p>
                        <button className="enter-button" id="enter-button" onClick={main_window.load_main_app_page}>Enter</button>
                     </div>
                </div>
            )
        }
    });
    ReactDOM.render(<HomePage />, document.getElementById('content'));
});


