define(["jquery", "react", "dom"], function($, React, ReactDOM) {
    // Color manipualation adapted from this:
    // http://stackoverflow.com/questions/16252448/how-to-calculate-the-proportional-color-between-the-three-given-with-a-percentage

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
        var factor;
        if (x < 50) {
            factor = (50 - x) / 50;
            return col[0].scale(factor).add(col[1].scale(1-factor));
        } else {
            factor = (100 - x) / 50;
            return col[2].scale(1-factor).add(col[1].scale(factor));
        }
    }

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
                canvas_height: 384,
                canvas_width: 384,
            };
        },
        get_context: function() {
            return document.getElementById(this.props.id).getContext("2d");
        },
        componentDidMount: function() {
            $("#" + this.props.id).mousemove(function(e){this.handle_mouse_move(e);}.bind(this));
        },
        handle_mouse_move: function (e) {
            var canvasOffset = $("#" + this.props.id).offset();
            mouseX = e.clientX - canvasOffset.left;
            mouseY = e.clientY - canvasOffset.top;
            pointX = Math.floor(mouseX / this.state.pixel_size);
            pointY = Math.floor(mouseY / this.state.pixel_size);
            value = this.state.data[pointX][pointY];
            if (value === undefined || value === "-1")
                value = "undefined";
            $('#current-data').text(pointX + ", " + pointY + ", " + value);
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
            diffed = [];
            // console.log("p", prev, "n", next);
            // console.log("prev", prev, "next", next);
            for (var x = 0; x < next.length; x++) {
                for (var y = 0; y < next[x].length; y++) {
                    if (next[x][y] !== prev[x][y]) {
                        diffed.push({x: x, y: y, z: next[x][y]});
                    }
                }
            }
            // console.log("Length of difference", diffed.length);
            // console.log(diffed, diffed.length);
            return diffed;
        },
        receive_data: function(data, min, max, data_length, is_switching_views) {
            // console.log("receiving data", data, min, max, data_length, is_switching_views);
            // console.log(data.length);
            // for (var i = 0; i < data.length; i++) {
            //     for (var j = 0; j < data[i].length; j++) {
            //         console.log(data[i][j] === 0);
            //     }
            // }
            var diff = this.diff_data(this.state.data, data);
            update_all = is_switching_views || !(this.state.running_max >= max && this.state.running_min <= min);
            // console.log(update_all);
            curr_data = this.state.data.slice();
            next_data = [];
            for (var i = 0; i < data.length; i++) {
                next_data.push([]);
                for (var j = 0; j < data[i].length; j++)
                    next_data[i].push(data[i][j]);
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
            for (var x = 0; x < data.length; x += 1) {
                for (var y = 0; y < data[x].length; y += 1) {
                    var z = data[x][y];
                    if (z === "-1")
                        continue;
                    this.draw_canvas_point(x, y, z, min, max, range, ctx);
                }
            }
        },
        draw_canvas_points: function(data, max, min) {
            // console.log("here", data.length);
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
            setTimeout(function(x, y, z, min, max, range, ctx) {
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
                ctx.fillRect(x * this.state.pixel_size, y * this.state.pixel_size, this.state.pixel_size, this.state.pixel_size);
            }.bind(this, x, y, z, min, max, range, ctx), 0);
        },
        dummy_data: function () {
            size = 256;
            this.change_pixel_size(size,size, function() {
                // console.log("here");
                var matrix = [];
                for(var i=0; i<256; i++) {
                    matrix[i] = new Array(256);
                }
                for (var i = 0; i < size; i++)
                    for (var j = 0; j < size; j++)
                        matrix[i][j] = i * j;

                this.receive_data(matrix, 0, (size -1)*(size -1), size * size, false);
            }.bind(this));
        },
        erase_data: function() {
            this.replaceState(this.getInitialState());
            var ctx = this.get_context();
            ctx.clearRect(0, 0, this.props.canvas_width, this.props.canvas_height);
            $('#current-data').text("");
        },
        eliminate_outliers: function (min, max) {
            new_data = this.state.data.slice();
            for (var x = 0; x < this.state.data.length; x++) {
                for (var y = 0; y < this.state.data[0].length; y++) {
                    if (this.state.data[x][y] < min) {
                        this.state.data[x][y] = min;
                        continue;
                    }
                    if (this.state.data[x][y] > max) {
                        this.state.data[x][y] = max;
                        continue;
                    }
                }
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
