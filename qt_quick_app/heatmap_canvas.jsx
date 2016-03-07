define(["jquery", "react", "dom"], function($, React, ReactDOM) {
    // Color manipualation adapted from this:
    // http://stackoverflow.com/questions/16252448/how-to-calculate-the-proportional-color-between-the-three-given-with-a-percentag
    var Colour = (function () {
        function limit(x) {
            if (x > 255) return 255;
            if (x < 0) return 0;
            return Math.floor(x);
        }
        function toHex(r, g, b) {
            if (r > 15) r = r.toString(16);
            else r = '0' + r.toString(16);
            if (g > 15) g = g.toString(16);
            else g = '0' + g.toString(16);
            if (b > 15) b = b.toString(16);
            else b = '0' + b.toString(16);
            return '#' + (r + g + b).toUpperCase();
        }
        function Colour(hex) {
            if (hex.length === 7 || hex.length === 4) hex = hex.slice(1);
            if (hex.length === 3)
                hex = hex.charAt(0) + hex.charAt(0)
                    + hex.charAt(1) + hex.charAt(1)
                    + hex.charAt(2) + hex.charAt(2);
            this.hex = '#' + hex.toUpperCase();
            this.r = parseInt(hex.slice(0, 2), 16);
            this.g = parseInt(hex.slice(2, 4), 16);
            this.b = parseInt(hex.slice(4, 6), 16);
        }
        Colour.prototype.scale = function (x) {
            var r = limit(this.r * x);
            var g = limit(this.g * x);
            var b = limit(this.b * x);
            return new Colour(toHex(r,g,b));
        };
        Colour.prototype.add = function (c) {
            return new Colour(
                toHex(
                    limit(this.r + c.r),
                    limit(this.g + c.g),
                    limit(this.b + c.b)
                )
            );
        };
        Colour.prototype.toString = function () {
            return this.hex;
        };
        Colour.prototype.valueOf = Colour.prototype.toString;
        return Colour;
    }());

    var myColours = [
        new Colour('#000000'), // Colour {hex: "#39BF26", r: 57, g: 191, b: 38, …}
        new Colour('#581C00'),  // Colour {hex: "#C7282E", r: 199, g: 40, b: 46, …}
        new Colour('#bc8000'), // Colour {hex: "#C7C228", r: 199, g: 194, b: 40, …}
        new Colour('#FcFc80'),
    ];

    function percent(x, col) {
        var bucket_size = 100 / (col.length - 1);
        for (var i = 1; i < col.length; i += 1) {
            var value = bucket_size * i;
            if (x <= value) {
                var factor = (value - x) / bucket_size;
                return col[i - 1].scale(1-factor).add(col[i].scale(factor));
            }
        }
        // if (x < 50) {
        //     factor = (50 - x) / 50;
        //     return col[0].scale(factor).add(col[1].scale(1-factor));
        // } else {
        //     factor = (100 - x) / 50;
        //     return col[2].scale(1-factor).add(col[1].scale(factor));
        // }
    }

    // for some reason num_rows and num_columns don't work properly when in state variables...
    // maybe should pass as props through scan.jsx
    var num_rows = scanner.num_rows();
    var num_columns = scanner.num_columns();

    var ScanHeatMap = React.createClass({
        getInitialState: function() {
            return {
                running_max: 0,
                running_min: 0,
                data: [],
                num_points: 0,
            };
        },
        getDefaultProps: function() {
            return {
                canvas_height: 256,
                canvas_width: 256,
            };
        },
        get_context: function() {
            return document.getElementById(this.props.id).getContext("2d");
        },
        componentDidMount: function() {
            scanner.new_offset_data.connect(this.handle_new_data);
            scanner.num_rows_changed.connect(this.change_num_rows);
            scanner.num_columns_changed.connect(this.change_num_columns);
        },
        change_num_rows: function(new_num_rows) {
            num_rows = new_num_rows;
        },
        change_num_columns: function(new_num_columns) {
            num_columns = new_num_columns;
        },
        handle_new_data: function(new_data) {
            var num_points = this.state.num_points;  // keep these variables local because operating on 
            // state actually works in its own queue, so it can't guarantee the values get set immediately,
            // which we need when operating in a loop
            var data = [];
            var max = this.state.running_max;
            var min = this.state.running_min;
            for (var i = 0; i < new_data.length / 2; i += 3) {
                num_points += 1;
                data.push({x: new_data[i], y: new_data[i+1], z: new_data[i+2]});
                max = Math.max(max, new_data[i+2]);
                min = Math.min(min, new_data[i+2]);
            }
            this.setState({
                num_points: num_points,
                data: this.state.data.concat(data),
                running_max: max,
                running_min: min,
            }, function() {
                this.redraw_canvas(this.state.data, this.state.running_max, this.state.running_min);
            }.bind(this));
        },
        redraw_canvas: function(data, max, min) {
            var ctx = this.get_context();
            var pixel_width = this.props.canvas_width/num_columns;
            var pixel_height = this.props.canvas_height/num_rows;
            var pixel_dimension = Math.min(pixel_width, pixel_height);
            for (var i = 0; i < data.length; i += 1) {
                var data_point = data[i];
                var color = percent((data_point.z - min)/(max - min) * 100, myColours);
                ctx.fillStyle = color.hex;
                ctx.fillRect(data_point.x * pixel_dimension, data_point.y * pixel_dimension, pixel_dimension, pixel_dimension);
            }
        },
        add_points: function() {
            var dummy_data = [];
            for (var i = 0; i < this.props.canvas_height; i += 1)
                for (var j = 0; j < this.props.canvas_width; j += 1) {
                    dummy_data.push(i);
                    dummy_data.push(j);
                    dummy_data.push(i*j);
                }
            this.handle_new_data(dummy_data);
        },
        erase_data: function() {
            this.replaceState(this.getInitialState());
            var ctx = this.get_context();
            ctx.clearRect(0, 0, this.props.canvas_width, this.props.canvas_height);
        },
        render: function() {
            return (
                <div>
                    <canvas id={this.props.id} style={{border: "1px solid black"}} height={this.props.canvas_height} width={this.props.canvas_width}>
                    </canvas>
                    <button className="action-button" onClick={this.add_points}>Add points</button>
                </div>
                    );
        }
    });
    return ScanHeatMap;
});