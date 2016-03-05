define(["jquery", "react", "dom"], function($, React, ReactDOM) {
    var ScanHeatMap = React.createClass({
        getDefaultProps: function() {
            return {
                min_value: 0,
                max_value: 4095,
            };
        },
        getInitialState: function() {

        },
        componentDidMount: function() {
            this.add_points();
        },
        context: function() {
            return document.getElementById(this.props.id).getContext("2d");
        },
        add_points: function() {
            var ctx = this.context;
            this.context.fillStyle = "#F00000";
            ctx.fillRect(0, 0, 20, 20);
        },
        render: function() {
            return (<canvas id={this.props.id} style={{border: "1px solid black"}}>
                    </canvas>);
        }
    });
    return ScanHeatMap;
});