define(["jquery", "react", "dom", "jsx!pages/sidebar"], function($, React, ReactDOM, Sidebar){
	var X = React.createClass({
		render: function() {
			return (<div><Sidebar />
				<div>l</div></div>)
		}
	});
	ReactDOM.render(<X />, document.getElementById('content'));
});