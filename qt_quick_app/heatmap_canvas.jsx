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
            var useful_data = new_data.slice(0, num_rows * 3);
            var update_all = true;
            if (this.state.running_max >= new_data[useful_data.length] && this.state.running_min <= new_data[useful_data.length + 1])
                update_all = false;
            this.setState({
                num_points: this.state.num_points + useful_data.length,
                data: this.state.data.concat(useful_data),
                running_max: Math.max(new_data[useful_data.length], this.state.running_max),
                running_min: Math.min(new_data[useful_data.length + 1], this.state.running_min)
            }, function() {
                this.redraw_canvas(update_all ? this.state.data : useful_data, this.state.running_max, this.state.running_min);
            });
        },
        receive_data: function(data, min, max) {
            update_all = !(this.state.running_max >= max && this.state.running_min <= min);
            this.setState({
                num_points: this.state.num_points + data.length,
                data: this.state.data.concat(data),
                running_max: Math.max(max, this.state.running_max),
                running_min: Math.min(min, this.state.running_min)
            }, function() {
                this.redraw_canvas_points(update_all ? this.state.data : data, this.state.running_max, this.state.running_min);
            });
        },
        redraw_canvas_points: function(data, max, min) {
            var ctx = this.get_context();
            var pixel_width = this.props.canvas_width/num_columns;
            var pixel_height = this.props.canvas_height/num_rows;
            var pixel_dimension = Math.min(pixel_width, pixel_height);
            var range = max - min;
            for (var i = 0; i < data.length; i += 1) {
                var x = data[i].x;
                var y = data[i].y;
                var z = data[i].value;
                setTimeout(function(x, y, z) {
                    var color;
                    if (max == min)
                        color = percent(0, myColours);
                    else
                        color = percent((z - min)/range * 100, myColours);
                    ctx.fillStyle = color.hex;
                    ctx.fillRect(x * pixel_dimension, y * pixel_dimension, pixel_dimension, pixel_dimension);
                }.bind(this, x, y, z), 0);
            }
        },
        redraw_canvas: function(data) {
            console.log("DATA LEN", data.length);
            var ctx = this.get_context();
            var pixel_width = this.props.canvas_width/num_columns;
            var pixel_height = this.props.canvas_height/num_rows;
            var pixel_dimension = Math.min(pixel_width, pixel_height);
            var range = max - min;
            for (var i = 0; i < data.length; i += 3) {
                var x = data[i];
                var y = data[i+1];
                var z = data[i+2];
                setTimeout(function(x, y, z) {
                    var color;
                    if (max == min)
                        color = percent(0, myColours);
                    else
                        color = percent((z - min)/range * 100, myColours);
                    ctx.fillStyle = color.hex;
                    ctx.fillRect(x * pixel_dimension, y * pixel_dimension, pixel_dimension, pixel_dimension);
                }.bind(this, x, y, z), 0);
            }
        },
        add_points: function() {
            var dummy_data = [];
            for (var i = 0; i < this.props.canvas_height; i += 1) {
                for (var j = 0; j < this.props.canvas_width; j += 1) {
                    dummy_data.push(i);
                    dummy_data.push(j);
                    dummy_data.push(i*j);
                }
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
                </div>
                    );
        }
    });
    return ScanHeatMap;
});