define(["jquery", "react", "dom"], function($, React, ReactDOM) {
    // Color manipualation adapted from this:
    // http://stackoverflow.com/questions/16252448/how-to-calculate-the-proportional-color-between-the-three-given-with-a-percentage

    var color_map = [];

    function two_d_matrix_generator(rows, cols) {
        var matrix = [];
        for(var i=0; i<rows; i++) {
            matrix.push([]);
            for (var j = 0; j < cols; j++) {
                matrix[i].push("-1");
            }
        }
        return matrix;
    }

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
        // Only works for 3 colours - should be generalized if you want to add more colours in the myColours array
        // to interpolate between
        var factor;
        if (x < 50) {
            factor = (50 - x) / 50;
            return col[0].scale(factor).add(col[1].scale(1-factor));
        } else {
            factor = (100 - x) / 50;
            return col[2].scale(1-factor).add(col[1].scale(factor));
        }
    }

    function populate_color_map() {
        for (var i = 0; i < 100; i += 0.01) {
            color_map.push(percent(parseFloat(i.toFixed(2)), myColours).hex);
        }
    }

    setTimeout(function()  {
        populate_color_map();
    }, 0);

    var ScanHeatMap = React.createClass({
        getInitialState: function() {
            return {
                running_max: Number.NEGATIVE_INFINITY,
                running_min: Number.POSITIVE_INFINITY,
                data: [],
                num_points: 0,
                pixel_size: 0,
            };
        },
        getDefaultProps: function() {
            return {
                canvas_height: 1024,
                canvas_width: 1024,
            };
        },
        get_context: function() {
            return document.getElementById(this.props.id).getContext("2d");
        },
        componentDidMount: function() {
            $("#" + this.props.id).mousemove(function(e){this.handle_mouse_move(e);}.bind(this));
            $("#" + this.props.id).click(function(e){this.handle_click(e);}.bind(this));
        },
        get_mouse_coordinate: function(e) {
            var canvasOffset = $("#" + this.props.id).offset();
            mouseX = e.clientX - canvasOffset.left;
            mouseY = e.clientY - canvasOffset.top;

            pointX = Math.floor(mouseX / this.state.pixel_size);
            pointY = Math.floor(mouseY / this.state.pixel_size);
            pointX = Math.max(pointX, 0);
            pointY = Math.max(pointY, 0);

            pointX = Math.min(pointX, this.props.canvas_width/this.state.pixel_size - 1);
            pointY = Math.min(pointY, this.props.canvas_height/this.state.pixel_size - 1);
            return {x: pointX, y: pointY};
        },
        handle_mouse_move: function (e) { // TODO: investigate if we can put this on a setTimeout 0 to avoid blocking the canvas rendering
            coord = this.get_mouse_coordinate(e);
            value = this.state.data[coord.y][coord.x];
            if (value === undefined || value === "-1")
                value = "undefined";
            $('#current-data').text(coord.x + ", " + coord.y + ", " + value);
        },
        handle_click: function (e) {
            coord = this.get_mouse_coordinate(e);
            this.props.handle_click(coord.x, coord.y);
        },
        change_pixel_size: function(num_rows, num_columns, callback) {
            this.setState({
                pixel_size: Math.min(this.props.canvas_width/num_columns, this.props.canvas_height/num_rows),
                data: two_d_matrix_generator(num_rows, num_columns),
            }, function() {
                if (callback)
                    callback();
            });
        },
        diff_data: function (prev, next) {
            // prev and next are complete data matrices
            diffed = [];
            var exit = false;
            for (var y = 0; y < next.length; y++) {
                if (exit) {
                    break;
                }
                for (var x = 0; x < next[y].length; x++) {
                    if (next[y][x] !== prev[y][x]) { // push different data
                        diffed.push({x: x, y: y, z: next[y][x]});
                    }
                    if (next[y][x] === "-1") {
                        exit = true;
                        break;
                    }
                }
            }
            // RETURNS a flat array of {x: y: z:} objects
            return diffed;
        },
        receive_data: function(data, min, max, data_length, is_switching_views) {
            var diff = this.diff_data(this.state.data, data);
            var update_all = is_switching_views || !(this.state.running_max >= max && this.state.running_min <= min);

            next_data = this.state.data; // copy the data to a new array to avoid weird pass by reference issues when setting this.state.data
            for (var i = 0; i < diff.length; i++) {
                next_data[diff[i].y][diff[i].x] = diff[i].z;
            }

            this.setState({
                num_points: data_length,
                data: next_data,
                running_max: (is_switching_views && max) || Math.max(max, this.state.running_max),
                running_min: (is_switching_views && min) || Math.min(min, this.state.running_min),
            }, function() {
                if (update_all) {
                    this.redraw_canvas_points(this.state.data, this.state.running_max, this.state.running_min);
                } else {
                    this.draw_canvas_points(diff, this.state.running_max, this.state.running_min);
                }
            });
        },
        redraw_canvas_points: function(data, max, min) {
            // takes a MxN array
            var ctx = this.get_context();
            var range = max - min;
            for (var y = 0; y < data.length; y += 1) {
                setTimeout(function(row) {
                    for (var x = 0; x < data[row].length; x += 1) {
                        var z = data[row][x];
                        if (z === "-1")
                            return;
                        this.draw_canvas_point(x, row, z, min, max, range, ctx);
                    }
                }.bind(this, y), 0);
            }
        },
        draw_canvas_points: function(data, max, min) {
            // takes a flat array of {x: y: z:} objects
            var ctx = this.get_context();
            var range = max - min;
            for (var i = 0; i < data.length; i += 1) {
                var x = data[i].x;
                var y = data[i].y;
                var z = data[i].z;
                this.draw_canvas_point(x, y, z, min, max, range, ctx);
            }
        },
        draw_canvas_point: function(x, y, z, min, max, range, ctx) {
            var pixel_size = this.state.pixel_size;
            if (max == min)
                color = color_map[0];
            else
                color = color_map[((z - min)/range * 10000) | 0];
            if (ctx.fillStyle != color)
                ctx.fillStyle = color;
            ctx.fillRect(x * pixel_size, y * pixel_size, pixel_size, pixel_size); // actually draw on the canvas
        },
        erase_data: function() {
            this.replaceState(this.getInitialState());
            var ctx = this.get_context();
            ctx.clearRect(0, 0, this.props.canvas_width, this.props.canvas_height);
            $('#current-data').text("");
        },
        eliminate_outliers: function (data, min, max) {
            data = data.slice();
            for (var y = 0; y < data.length; y++) {
                for (var x = 0; x < data[0].length; x++) {
                    if (data[y][x] < min) {
                        data[y][x] = min;
                        continue;
                    }
                    if (data[y][x] > max) {
                        data[y][x] = max;
                        continue;
                    }
                }
            }
            this.redraw_canvas_points(data, max, min);
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
