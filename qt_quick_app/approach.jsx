 define(["react", "jsx!pages/approach_graph"], function(React, Graph) {
	var Approach = React.createClass({
		render: function() {
			return (
				<div>
					<button onClick={approacher.cmd_start_auto_approach}>Approach</button>
					{Graph}
				</div>)
		},
	});
	return Approach;
});
