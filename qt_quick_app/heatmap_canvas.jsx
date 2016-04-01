define(["jquery", "react", "dom"], function($, React, ReactDOM) {
    // Color manipualation adapted from this:
    // http://stackoverflow.com/questions/16252448/how-to-calculate-the-proportional-color-between-the-three-given-with-a-percentage
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
        new Colour('#581C00'),
        new Colour('#bc8000'),
        new Colour('#FcFc80'),
    ];
    
    function percent(x, col) {
        var factor;
        if (x < 50) {
            factor = (50 - x) / 50;
            return col[0].scale(factor).add(col[1].scale(1-factor));
        } else {
            factor = (100 - x) / 50;
            return col[2].scale(1-factor).add(col[1].scale(factor));
        }
    }

    // for some reason num_rows and num_columns don't work properly when in state variables...
    // maybe should pass as props through scan.jsx
    var num_rows = scanner.num_rows();
    var num_columns = scanner.num_columns();

    var ScanHeatMap = React.createClass({
        getInitialState: function() {
            return {
                running_max: Number.NEGATIVE_INFINITY,
                running_min: Number.POSITIVE_INFINITY,
                data: [],
                num_points: 0,
            };
        },
        getDefaultProps: function() {
            return {
                canvas_height: 384,
                canvas_width: 384,
            };
        },
        get_context: function() {
            return document.getElementById(this.props.id).getContext("2d");
        },
        componentDidMount: function() {
            scanner.num_rows_changed.connect(this.change_num_rows);
            scanner.num_columns_changed.connect(this.change_num_columns);
            $("#" + this.props.id).mousemove(function(e){this.handle_mouse_move(e);}.bind(this));
        },
        handle_mouse_move: function (e) {
            var canvasOffset = $("#" + this.props.id).offset();
            mouseX = e.clientX - canvasOffset.left;
            mouseY = e.clientY - canvasOffset.top;
            pointX = Math.floor(mouseX * num_columns/this.props.canvas_width);
            pointY = Math.floor(mouseY * num_rows/this.props.canvas_height);
            for (var i = 0; i < this.state.data.length; i++) {
                if (this.state.data[i].x == pointX && this.state.data[i].y == pointY) {
                    $('#current-data').text(pointX + ", " + pointY + ", " + this.state.data[i].value);
                    return;
                }
            }
            $('#current-data').text("");
        },
        change_num_rows: function(new_num_rows) {
            num_rows = new_num_rows;
        },
        change_num_columns: function(new_num_columns) {
            num_columns = new_num_columns;
        },
        receive_data: function(data, min, max, num_points_to_draw, is_switching_views) {
            if (!is_switching_views) {
                update_all = !(this.state.running_max >= max && this.state.running_min <= min);
                this.setState({
                    num_points: data.length,
                    data: data,
                    running_max: Math.max(max, this.state.running_max),
                    running_min: Math.min(min, this.state.running_min)
                }, function() {
                    this.redraw_canvas_points(update_all ? this.state.data : this.state.data.slice(this.state.data.length - num_points_to_draw), this.state.running_max, this.state.running_min);
                });
            } else {
                this.setState({
                    num_points: data.length,
                    data: data,
                    running_max: max,
                    running_min: min,
                }, function() {
                    this.redraw_canvas_points(this.state.data, this.state.running_max, this.state.running_min);
                });
            }
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
                    try {
                        ctx.fillStyle = color.hex;
                    } catch (e) {
                        console.log(e, color, x, y, z, min, max, range);
                    }
                    ctx.fillRect(x * pixel_dimension, y * pixel_dimension, pixel_dimension, pixel_dimension);
                }.bind(this, x, y, z), 0);
            }
        },
        dummy_data: function () {
            data = [];
            for (var i = 0; i < 20; i++)
                for (var j = 0; j < 20; j++)
                    data.push({x: i, y: j, value: i * j});
            this.receive_data(data, 0, 19*19, 20*20, false);
        },
        erase_data: function() {
            this.replaceState(this.getInitialState());
            var ctx = this.get_context();
            ctx.clearRect(0, 0, this.props.canvas_width, this.props.canvas_height);
            $('#current-data').text("");
        },
        eliminate_outliers: function (min, max) {
            new_data = [];
            for (var i = 0; i < this.state.data.length; i++) {
                var x = this.state.data[i].x;
                var y = this.state.data[i].y;
                var value = this.state.data[i].value;
                if (value < min) {
                    new_data.push({x: x, y: y, value: min});
                    continue;
                }
                if (value > max) {
                    new_data.push({x: x, y: y, value: max});
                    continue;
                }
                new_data.push({x: x, y:y, value: value});
            }
            this.redraw_canvas_points(new_data, max, min);
        },
        render: function() {
            return (
                <div>
                    <canvas id={this.props.id} style={{border: "1px solid black"}} height={this.props.canvas_height} width={this.props.canvas_width}>
                    </canvas>
                    <p><span>Hovered point: </span><span id="current-data"></span></p>
                </div>
                    );
        }
    });
    return ScanHeatMap;
});
