define(["react", "jsx!pages/heatmap_canvas", "jsx!pages/line_profile", "jsx!pages/inline_scan_controls", "jsx!pages/number_input", "jsx!pages/dropdown", "jsx!pages/text_input", "jsx!pages/save_folder", "jsx!pages/scan_range_slider"], function(React, HeatmapCanvas, LineProfile, InlineScanControls, NumberInput, Dropdown, TextInput, SaveFolderPicker, ScanRangeSlider) {
    var empty_image_str = "data:image/gif;base64,R0lGODlhAAQABIAAAP///////yH+EUNyZWF0ZWQgd2l0aCBHSU1QACH5BAEKAAEALAAAAAAABAAEAAL+jI+py+0Po5y02ouz3rz7D4biSJbmiabqyrbuC8fyTNf2jef6zvf+DwwKh8Si8YhMKpfMpvMJjUqn1Kr1is1qt9yu9wsOi8fksvmMTqvX7Lb7DY/L5/S6/Y7P6/f8vv8PGCg4SFhoeIiYqLjI2Oj4CBkpOUlZaXmJmam5ydnp+QkaKjpKWmp6ipqqusra6voKGys7S1tre4ubq7vL2+v7CxwsPExcbHyMnKy8zNzs/AwdLT1NXW19jZ2tvc3d7f0NHi4+Tl5ufo6err7O3u7+Dh8vP09fb3+Pn6+/z9/v/w8woMCBBAsaPIgwocKFDBs6fAgxosSJFCtavIgxo8b+jRw7evwIMqTIkSRLmjyJMqXKlSxbunwJM6bMmTRr2ryJM6fOnTx7+vwJNKjQoUSLGj2KNKnSpUybOn0KNarUqVSrWr2KNavWrVy7ev0KNqzYsWTLmj2LNq3atWzbun0LN67cuXTr2r2LN6/evXz7+v0LOLDgwYQLGz6MOLHixYwbO34MObLkyZQrW76MObPmzZw7e/4MOrTo0aRLmz6NOrXq1axbu34NO7bs2bRr276NO7fu3bx7+/4NPLjw4cSLGz+OPLny5cybO38OPbr06dSrW7+OPbv27dy7e/8OPrz48eTLmz+PPr369ezbu38PP778+fTr27+PP7/+/fz++/v/D2CAAg5IYIEGHohgggouyGCDDj4IYYQSTkhhhRZeiGGGGm7IYYcefghiiCKOSGKJJp6IYooqrshiiy6+CGOMMs5IY4023ohjjjruyGOPPv4IZJBCDklkkUYeiWSSSi7JZJNOPglllFJOSWWVVl6JZZZabslll15+CWaYYo5JZplmnolmmmquyWabbr4JZ5xyzklnnXbeiWeeeu7JZ59+/glooIIOSmihhh6KaKKKLspoo44+Cmmkkk5KaaWWXopppppuymmnnn4Kaqiijkpqqaaeimqqqq7KaquuvgprrLLOSmuttt6Ka6667sprr77+Cmywwg5LbLHGHov+bLLKLstss84+C2200k5LbbXWXottttpuy2233n4Lbrjijktuueaei2666q7LbrvuvgtvvPLOS2+99t6Lb7767stvv/7+C3DAAg9McMEGH4xwwgovzHDDDj8MccQST0xxxRZfjHHGGm/McccefwxyyCKPTHLJJp+Mcsoqr8xyyy6/DHPMMs9Mc80234xzzjrvzHPPPv8MdNBCD0100UYfjXTSSi/NdNNOPw111FJPTXXVVl+NddZab811115/DXbYYo9Ndtlmn4122mqvzXbbbr8Nd9xyz0133XbfjXfeeu/Nd99+/w144IIPTnjhhh+OeOKKL854444/Dnnkkk/+Tnnlll+Oeeaab855555/Dnrooo9Oeummn4566qqvznrrrr8Oe+yyz0577bbfjnvuuu/Oe+++/w588MIPT3zxxh+PfPLKL898884/D3300k9PffXWX4999tpvz3333n8Pfvjij09++eafj3766q/Pfvvuvw9//PLPT3/99t+Pf/76789///7/D8AACnCABCygAQ+IwAQqcIEMbKADHwjBCEpwghSsoAUviMEManCDHOygBz8IwhCKcIQkLKEJT4jCFKpwhSxsoQtfCMMYynCGNKyhDW+IwxzqcIc87KEPfwjEIApxiEQsohGPiMQkKnGJTGyiE58IxShKcYpUrKL+Fa+IxSxqcYtc7KIXvwjGMIpxjGQsoxnPiMY0qnGNbGyjG98IxzjKcY50rKMd74jHPOpxj3zsox//CMhACnKQhCykIQ+JyEQqcpGMbKQjHwnJSEpykpSspCUviclManKTnOykJz8JylCKcpSkLKUpT4nKVKpylaxspStfCctYynKWtKylLW+Jy1zqcpe87KUvfwnMYApzmMQspjGPicxkKnOZzGymM58JzWhKc5rUrKY1r4nNbGpzm9zspje/Cc5winOc5CynOc+JznSqc53sbKc73wnPeMpznvSspz3vic986nOf/OynP/8J0IAKdKAELahBD4rQhCp0oQxtqEPbHwrRiEp0ohStqEUvitGManSjHO2oRz8K0pCKdKQkLalJT4rSlKp0pSxtqUtfCtOYynSmNK2pTW+K05zqdKc87alPfwrUoAp1qEQtqlGPitSkKnWpTG2qU58K1ahKdapUrapVr4rVrGp1q1ztqle/CtawinWsZC2rWc+K1rSqda1sbatb3wrXuMp1rnStq13vite86nWvfO2rX/8K2MAKdrCELaxhD4vYxCp2sYxtrGMfC9nISnaylK2sZS+L2cxqdrOc7axnPwva0Ip2tKQtrWlPi9rUqna1uCsAADs=";
    var empty_bar_str = "data:image/gif;base64,R0lGODlhgAAABIAAAP///////yH+EUNyZWF0ZWQgd2l0aCBHSU1QACH5BAEKAAEALAAAAACAAAAEAAL+jI+py+0Po5y02ouz3rz7D4biSJbmiabqyrbuC8fyTNf2jef6zvf+DwwKh8Si8YhMKpfMpvMJjUqn1Kr1is1qt9yu9wsOi8fksvmMTqvX7Lb7DY/L5/S6/Y7P6/f8vv8PGCg4SFhoeIiYqLjI2Oj4CBkpOUlZaXmJmam5ydnp+QkaKjpKWmp6ipqqusra6voKGys7S1tre4ubq7vL2+v7CxwsPExcbHyMnKy8zNzs/AwdLT1NXW19jZ2tvc3d7f0NHi4+Tl5ufo6err7O3u7+Dh8vP09fb3+Pn6+/z9/v/w8woMCBBAsaPIgwocKFDBs6fAgxosSJFCtavIgxo8b+jRw7evwIMqTIkSRLmjyJMqXKlSxbunwJM6bMmTRr2ryJM6fOnTx7+vwJNKjQoUSLGj2KNKnSpUybOn0KNarUqVSrWr2KNavWrVy7ev0KNqzYsWTLmj2LNq3atWzbun0LN67cuXTr2r2LN6/evXz7+v0LOLDgwYQLGz6MOLHixYwbO34MObLkyZQrW76MObPmzZw7e/4MOrTo0aRLmz6NOrXq1axbu34NO7bs2bRr276NO7fu3bx7+/4NPLjw4cSLGz+OPLny5cybO38OPbr06dSrW7+OPbv27dy7e/8OPrz48eTLmz+PPr369ezbu38PP778+fTr27+PP7/+/fwL+/v/D2CAAg5IUAEAOw==";
    function ScanView(name, render_signal, data_source) {
        this.name = name;
        this.data_source = data_source;
        this.render_signal = render_signal;
        this.data = empty_image_str;
        this.leveled_data = empty_image_str;
        this.image_ready = true;
        this.line_view_ready = true;
        this.z_bar_data = empty_bar_str;
        this.leveled_z_bar_data = empty_bar_str;
        this.z_bar_ready = true;
    }

    var scan_views = [];
    scan_views.push(new ScanView("Forward Offset", scanner.new_forward_offset_data,scanner.new_forward_offset_profile));
    scan_views.push(new ScanView("Forward Error", scanner.new_forward_error_data, scanner.new_forward_error_profile));
    scan_views.push(new ScanView("Forward Phase",  scanner.new_forward_phase_data, scanner.new_forward_phase_profile));
    scan_views.push(new ScanView("Reverse Offset",  scanner.new_reverse_offset_data, scanner.new_reverse_offset_profile));
    scan_views.push(new ScanView("Reverse Error",  scanner.new_reverse_error_data, scanner.new_reverse_error_profile));
    scan_views.push(new ScanView("Reverse Phase",  scanner.new_reverse_phase_data, scanner.new_reverse_phase_profile));

    // only apply leveling to topo
    var level_enable_scans = {};
    level_enable_scans[scan_views[0].name] = true;
    level_enable_scans[scan_views[3].name] = true;

    var Scan = React.createClass({
        getInitialState: function() {
            return {
                scanning: false,
                starting_fresh_scan: true,
                current_image: "Forward Offset",
                level_image: false,
                current_line: 0,
                num_rows: 16,
                num_columns: 16,
                advanced: false,
                line_profile_width: 1,
                line_profile_y: 0,
                zoom_set: false,
                dragging: false,
                mouse_start_x: 0,
                mouse_start_y: 0,
                save_folder: "",
                save_message: "",
                auto_save: false,
                continuous_scan: false,
                save_png: false,
                data_saved: false,
            };
        },
        componentWillReceiveProps : function(nextProps) {
            if (nextProps.showStep === false) {
                $('#scan-wrapper').hide();
            } else {
                $('#scan-wrapper').show();
                this.refs.line_profile.reflow();
            }
        },
        pause_scanning: function() {
            this.setState({
                scanning: false,
            }, function(){
                scanner.pause_state_machine();
            });
        },
        set_scan_complete: function() {
            this.setState({
                scanning: false,
                starting_fresh_scan: true,
            });
        },
        handle_all_processing_done: function() {
            if(this.state.auto_save){
                this.save_data();
            }
            if(this.state.continuous_scan){
                this.start_or_resume_scanning();
            }
        },
        componentDidMount: function() {

            scanner.num_rows_changed.connect(this.change_num_rows);
            scanner.num_columns_changed.connect(this.change_num_columns);
            scanner.all_data_received.connect(this.set_scan_complete);
            scanner.all_processing_done.connect(this.handle_all_processing_done);
            afm.save_folder_changed.connect(this.save_folder_changed);
            // connect scan views to their data sources
            for (var i = 0; i < scan_views.length; i++) {
                var bound_method = this.handle_png_data.bind(this, scan_views[i]);
                scan_views[i].render_signal.connect(bound_method);
                bound_method = this.prepare_line_profile.bind(this, scan_views[i]);
                scan_views[i].data_source.connect(bound_method);
            }
            // put blue marker on the first button
            $('.view-selector-button').first().addClass('selected-scan-view');
            $(document).mouseup(this.handle_mouse_up);
        },
        handle_png_data: function(scan_view, new_data){
            if(new_data[0]) {
                this.setState({ current_line: new_data[0]});
            }
            if(new_data[1]) { //raw_png
                scan_view.data = "data:image/png;base64," + new_data[1];
            }
            if(new_data[2]){ //raw_png_z_scale
                scan_view.z_bar_data = "data:image/png;base64," + new_data[2];
            }
            if(new_data[3]) { //leveled_png
                scan_view.leveled_data = "data:image/png;base64," + new_data[3];
            }
            if(new_data[4]){ //leveled_png_z_scale
                scan_view.leveled_z_bar_data = "data:image/png;base64," + new_data[4];
            }
            if(scan_view.name == this.state.current_image){
                if(new_data[1] || new_data[3]) { //if updated image data
                    this.schedule_image_update(scan_view);
                }
                if(new_data[2] || new_data[4]) { //if updated z_bar
                    this.schedule_z_bar_update(scan_view);
                }
            }
        },
        schedule_image_update: function(scan_view) {
            if (scan_view.image_ready) {
                scan_view.image_ready = false;
                setTimeout(function(){
                    scan_view.image_ready = true;
                }, 125);
                this.update_image((this.state.use_level && (scan_view.name in level_enable_scans)) ? scan_view.leveled_data : scan_view.data);
            }
        },
        schedule_z_bar_update: function(scan_view) {
            if (scan_view.z_bar_ready) {
                scan_view.z_bar_ready = false;
                setTimeout(function(){
                    scan_view.z_bar_ready = true;
                }, 125);
                this.update_z_bar((this.state.use_level && (scan_view.name in level_enable_scans)) ? scan_view.leveled_z_bar_data : scan_view.z_bar_data);
            }
        },
        update_image: function(data) {
            var element = $('.scan-image');
            element.data("imgsrc", data);
            element[0].src = element.data('imgsrc');
        },
        update_z_bar: function(data) {
            var bar = $('.scan-z-scalebar');
            bar.data("imgsrc", data);
            bar[0].src = bar.data('imgsrc');
        },
        change_num_rows: function (num_rows) {
            this.setState({
                num_rows: num_rows,
            });
        },
        change_num_columns: function (num_cols) {
            this.setState({
                num_columns: num_cols,
            });
        },
        prepare_line_profile: function (scan_view, data) {
            if (scan_view.name.charAt(8) == this.state.current_image.charAt(8)) {
                if (scan_view.line_view_ready) {
                    scan_view.line_view_ready = false;
                    setTimeout(function(){
                        scan_view.line_view_ready = true;
                    }, 200);
                    setTimeout(function(){
                        var scan_data = [];
                        var count_by = Math.ceil(data.length / 256); // limit resolution to 256
                        for (var i = 0; i < data.length; i += 3*count_by) {
                            scan_data.push({x: data[i], y: data[i+2]});
                        }
                        if (scan_view.name.charAt(0) == 'F') {
                            this.refs.line_profile.set_data(scan_data, null);
                        } else {
                            this.refs.line_profile.set_data(null, scan_data);
                        }
                    }.bind(this), 0);
                }
            }
        },
        push_data_to_view: function(scan_view, is_switching_views) {
            this.refs.line_profile.set_data(scan_view.forward_data.most_recent_line_profile(), scan_view.reverse_data.most_recent_line_profile());
        },
        // TODO: this whole tristate scanning button really should just be done with a dictionary
        start_or_resume_scanning: function() {
            this.setState({
                num_rows: scanner.num_rows(),
                num_columns: scanner.num_columns(),
            });
            this.setState({
                scanning: true,
            }, function(){
                if (this.state.starting_fresh_scan) {
                    scanner.start_state_machine();
                    this.setState({data_saved: false});
                    for (var i = 0; i < scan_views.length; i++) {
                        scan_views[i].data = empty_image_str;
                        scan_views[i].z_bar_data = empty_bar_str;
                        scan_views[i].leveled_data = empty_image_str;
                        scan_views[i].leveled_z_bar_data = empty_bar_str;
                    }
                    $('.scan-image-inverter').css({
                        "margin-top": 0,
                        "margin-bottom": "100%"
                    });
                    this.setState({
                        starting_fresh_scan: false
                    });
                } else {
                    scanner.resume_state_machine();
                }
            });
        },
        clear_scan: function() {
            this.pause_scanning();
            scanner.reset();
            this.setState({data_saved: false});
            setTimeout(function() {
                for (var i = 0; i < scan_views.length; i++) {
                    scan_views[i].data = empty_image_str;
                    scan_views[i].z_bar_data = empty_bar_str;
                    scan_views[i].leveled_data = empty_image_str;
                    scan_views[i].leveled_z_bar_data = empty_bar_str;
                }
                this.update_image(empty_image_str);
                this.update_z_bar(empty_bar_str);
                $('.scan-image-inverter').css({
                    "margin-top": 0,
                    "margin-bottom": "100%"
                });
                this.refs.line_profile.erase_data();
                this.set_scan_complete();
            }.bind(this), 200); // give time for the scnaner to actually pause
            // so data doesn't get rendered
            // (maybe this should happen on a signal) or have a "accepting data" state check before dispatching
        },
        eliminate_outliers: function() {
            current_data_container = this.state.current_view % 2 === 0 ? scan_views[Math.floor(this.state.current_view / 2)].forward_data : scan_views[Math.floor(this.state.current_view / 2)].reverse_data;
            current_heatmap = current_data_container.heatmap;
            var rms = Math.sqrt(current_data_container.sum_of_squares / current_data_container.num_points);
            var mean = current_data_container.sum / current_data_container.num_points;
            var rms_multiplier = scanner.rms_threshold();
            var min = Math.max(mean - rms_multiplier * rms, current_data_container.min);
            var max = Math.min(mean + rms_multiplier * rms, current_data_container.max);
            // this.refs.heatmap.eliminate_outliers(current_heatmap, min, max);
            this.refs.line_profile.draw_outlier_plotlines(min, max);
        },
        handle_view_selector_click: function(image_name, e) {
            // Set style of selected name
            var target = $(e.target);
            $('.view-selector-button').removeClass('selected-scan-view');
             // for some reason the click events sometimes register under the p tag, sometimes under the span
            if (target.is('p')) {
                target.addClass('selected-scan-view');
            } else if (target.is('span')) {
                target.parent().addClass("selected-scan-view");
            }

            if (image_name.charAt(8) == 'O') {
                // offset
                this.refs.line_profile.set_y_label("Offset (nm)", true);
            } else if (image_name.charAt(8) == 'E') {
                this.refs.line_profile.set_y_label("Error (mV)", true);
            } else {
                // generic
                this.refs.line_profile.set_y_label("Magnitude", true);
            }

            this.setState({current_image: image_name}, function() {
                for(i=0; i<scan_views.length; i++) {
                    if (scan_views[i].name == this.state.current_image) {
                        this.update_image((this.state.use_level && (this.state.current_image in level_enable_scans)) ? scan_views[i].leveled_data : scan_views[i].data);
                        this.update_z_bar((this.state.use_level && (this.state.current_image in level_enable_scans)) ? scan_views[i].leveled_z_bar_data : scan_views[i].z_bar_data);
                    }
                }
                if(this.state.current_image in level_enable_scans){
                    $("#use_level_checkbox").css("visibility", "visible");
                }
                else {
                    $("#use_level_checkbox").css("visibility", "hidden");
                }
            });
        },
        handle_image_mouse_move: function(e) {
            if (!this.state.scanning && this.state.starting_fresh_scan) {
                var img = $('.scan-image');
                if(!this.state.dragging) {
                    // line profile
                    var aspect_ratio = this.state.num_rows/ img[0].clientHeight;
                    var offsetY = e.pageY - img.offset().top;
                    if(offsetY < 0){offsetY = 0;}
                    this.setState({line_profile_y: offsetY*aspect_ratio}, function(){
                        scanner.fetch_line_profiles(Math.floor(this.state.line_profile_y), this.state.line_profile_width);
                        $('.scan-image-inverter').css({
                            "margin-top": Math.max(offsetY - this.state.line_profile_width/aspect_ratio/2, 0),
                            "margin-bottom": Math.max(img[0].clientHeight - offsetY - this.state.line_profile_width/aspect_ratio/2, 0)
                        });
                    });
                } else {
                    // zoom
                    var offsetX = e.pageX - img.offset().left;
                    var offsetY = e.pageY - img.offset().top;
                    var square_size = Math.max(offsetX - this.state.mouse_start_x, offsetY - this.state.mouse_start_y);
                    if (square_size > 0) {
                        $('.scan-image-inverter').css({
                            "margin-bottom": Math.max(img[0].clientHeight - (this.state.mouse_start_y + square_size), 0),
                            "margin-right": Math.max(img[0].clientWidth - (this.state.mouse_start_x + square_size), 0)
                        });
                    }
                }
            }
        },
        handle_image_mouse_wheel: function(e) {
            if (!this.state.scanning && this.state.starting_fresh_scan && !this.state.dragging) {
                var new_width = this.state.line_profile_width;
                if (e.deltaY < 0) new_width += 2; // scrolling up
                if (e.deltaY > 0) new_width -= 2; // scrolling down
                if (new_width < 1) new_width = 1;
                if (new_width > this.state.num_rows*2 + 1) new_width = this.state.num_rows*2 + 1; // restrict width to cover the entire image at max from one end of image
                var img = $('.scan-image');
                var aspect_ratio = this.state.num_rows / img[0].clientHeight;
                var offsetY = this.state.line_profile_y/aspect_ratio;
                e.preventDefault();
                this.setState({line_profile_width: new_width}, function(){
                    scanner.fetch_line_profiles(Math.floor(this.state.line_profile_y ), this.state.line_profile_width);
                    $('.scan-image-inverter').css({
                        "margin-top": Math.max(offsetY - this.state.line_profile_width/aspect_ratio/2, 0),
                        "margin-bottom": Math.max(img[0].clientHeight - offsetY - this.state.line_profile_width/aspect_ratio/2, 0)
                    });
                });
            }
        },
        handle_image_mouse_leave: function(e) {
            if (!this.state.dragging) {
                $('.scan-image-inverter').css({
                    "margin-top": 0,
                    "margin-bottom": "100%"
                });
            }
        },
        handle_image_mouse_down: function(e) {
            if (!this.state.scanning && this.state.starting_fresh_scan) {
                var img = $('.scan-image');
                var offsetX = e.pageX - img.offset().left;
                var offsetY = e.pageY - img.offset().top;
                this.setState({dragging: true,
                               mouse_start_x: offsetX,
                               mouse_start_y: offsetY}, function(){
                    $('.scan-image-inverter').css({
                        "margin-top": offsetY,
                        "margin-bottom": img[0].clientHeight - offsetY,
                        "margin-left": offsetX,
                        "margin-right": img[0].clientWidth - offsetX
                    });
                });
            }
        },
        handle_mouse_up: function(e) {
            if (!this.state.scanning && this.state.starting_fresh_scan && this.state.dragging) {
                var img = $('.scan-image');
                var offsetX = e.pageX - img.offset().left;
                var offsetY = e.pageY - img.offset().top;
                offsetX = Math.min(offsetX, img[0].clientWidth);
                offsetY = Math.min(offsetY, img[0].clientHeight);
                var square_size = Math.max(offsetX - this.state.mouse_start_x, offsetY - this.state.mouse_start_y);
                if (square_size > 0) {
                    scanner.zoom(this.state.mouse_start_x / img[0].clientWidth,
                                 this.state.mouse_start_y / img[0].clientHeight,
                                 square_size / img[0].clientWidth);
                    this.setState({zoom_set: true});
                }
                this.setState({dragging: false}, function() {
                    $('.scan-image-inverter').css({
                        "margin-top": 0,
                        "margin-bottom": "100%",
                        "margin-left": 0,
                        "margin-right": 0
                    });
                });
            }
        },
        handle_level_change: function(e) {
            this.setState(
                {use_level: e.target.checked},
                function() {
                    scanner.set_use_level(this.state.use_level);
                    for(i=0; i<scan_views.length; i++) {
                        if (scan_views[i].name == this.state.current_image) {
                            this.update_image((this.state.use_level && (this.state.current_image in level_enable_scans)) ? scan_views[i].leveled_data : scan_views[i].data);
                            this.update_z_bar((this.state.use_level && (this.state.current_image in level_enable_scans)) ? scan_views[i].leveled_z_bar_data : scan_views[i].z_bar_data);
                        }
                    }
                    if (!this.state.scanning && this.state.starting_fresh_scan) {
                        scanner.fetch_line_profiles(Math.floor(this.state.line_profile_y ), this.state.line_profile_width);
                    }
                    if (!this.state.scanning && !this.state.starting_fresh_scan) {
                        console.log("js enter fetch latest")
                        scanner.fetch_latest_offset_profiles();
                    }
                });
        },
        get_specific_row_profile: function(data, y_value) {
            return data.slice(y_value * this.state.num_columns, (y_value + 1) * this.state.num_columns);
        },
        handle_heatmap_click: function(x, y) {
            var current_data_set = scan_views[Math.floor(this.state.current_view / 2)];
            this.refs.line_profile.set_data(current_data_set.profile[y], current_data_set.reverse_data.profile[y]);
        },
        toggle_advanced_controls: function () {
            this.setState({
                advanced: !this.state.advanced
            });
        },
        save_data: function () {
            if(this.state.save_folder && scanner.base_file_name()) {
                status_message = afm.save_scan_data();
                this.set_save_message_with_clear(status_message);
                if(status_message == "Save success")
                    this.setState({data_saved: true});
            }
            else {
                this.set_save_message_with_clear("Please specify save folder and file name base");
            }
        },
        set_save_message_with_clear: function(msg) {
            this.setState(
                {save_message: msg},
                function() {
                    $(".save-message").fadeTo("fast",1);
                    setTimeout(function() {
                        $(".save-message").fadeTo("slow",0);
                    }.bind(this), 2000);
                }.bind(this)
            );
        },
        save_folder_changed: function(data) {
            this.setState({save_folder: data});
        },
        handle_auto_save_change: function(e) {
            this.setState({auto_save: e.target.checked});
        },
        handle_save_png_change: function(e) {
            this.setState(
                {save_png: e.target.checked},
                function() {
                    scanner.set_save_png(this.state.save_png);
                });
        },
        handle_continuous_scan_change: function(e) {
            this.setState({continuous_scan: e.target.checked});
        },
        reset_zoom: function () {
            scanner.reset_zoom();
            this.setState({zoom_set:false});
        },
        render: function() {
             // the states will need fixing - clean button should be disabled until scanning completely done (should edit how states work)
            return (
                <div className="wrapper" id="scan-wrapper">
                    <div className="left-flexbox flexbox-row">
                        <div className="scan-view-selector-container">
                            <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "Forward Offset")}> Forward Topo</p>
                            <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "Reverse Offset")}> Reverse Topo</p>
                            <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "Forward Phase")}> Forward Phase</p>
                            <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "Reverse Phase")}> Reverse Phase</p>
                            <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "Forward Error")}> Foward Error</p>
                            <p className="view-selector-button" onClick={this.handle_view_selector_click.bind(this, "Reverse Error")}> Reverse Error</p>
                        </div>
                        <div className="flex-column">
                            <div className="scan-window-container">
                                <div className="scan-images-container">
                                    <img src={empty_image_str} className="scan-image"
                                        onMouseMove={this.handle_image_mouse_move}
                                        onWheel={this.handle_image_mouse_wheel}
                                        onMouseLeave={this.handle_image_mouse_leave}
                                        onMouseDown={this.handle_image_mouse_down}
                                        draggable="false"
                                    />
                                    <div className="scan-image-inverter" />
                                </div>
                                <div className="scan-z-scalebar-container">
                                    <img src={empty_bar_str} className="scan-z-scalebar"/>
                                </div>
                            </div>
                            <LineProfile ref="line_profile" chart_name={this.props.name}/>
                        </div>
                    </div>
                    <div className="right-flexbox">
                        <div className="step-name">Scan</div>
                        <div className="step-description">
                            Press "Scan" to begin imaging.
                        </div>
                        <div id="scan-dropdown-container">
                            <Dropdown options_list={[
                                        {text: "8", cmd_number: 8},
                                        {text: "16", cmd_number: 16},
                                        {text: "32", cmd_number: 32},
                                        {text: "64", cmd_number: 64},
                                        {text: "128", cmd_number: 128},
                                        {text: "256", cmd_number: 256},
                                        {text: "512", cmd_number: 512},
                                        {text: "1024", cmd_number: 1024},
                                    ]}
                                    selection_method={scanner.set_num_columns}
                                    notify_signal={scanner.num_columns_changed}
                                    get_value={scanner.num_columns}
                                    title="Number of pixels per line"/>
                            <Dropdown options_list={[
                                        {text: "8", cmd_number: 8},
                                        {text: "16", cmd_number: 16},
                                        {text: "32", cmd_number: 32},
                                        {text: "64", cmd_number: 64},
                                        {text: "128", cmd_number: 128},
                                        {text: "256", cmd_number: 256},
                                        {text: "512", cmd_number: 512},
                                        {text: "1024", cmd_number: 1024},
                                    ]}
                                    selection_method={scanner.set_num_rows}
                                    notify_signal={scanner.num_rows_changed}
                                    get_value={scanner.num_rows}
                                    title="Number of lines"/>
                            <ScanRangeSlider name="Scan Range" qt_objects={[pga_x_1, pga_x_2, pga_y_1, pga_y_2]}
                                      is_line = {function(){ return scanner.ratio() == 1; }}
                                      is_line_changed = {scanner.ratio_changed} />
                            <NumberInput value_type="scan"
                                        name="Time spent at each point (us)"
                                        min={0}
                                        max={2550}
                                        step={10}
                                        round={-1}
                                        notify_signal={scanner.dwell_time_changed}
                                        get_value={scanner.dwell_time}
                                        set_value={scanner.set_dwell_time} />
                        </div>
                        <div className="save-row">
                            <div className="flex-resize">
                                <div className="pointer-cursor overflow-hidden" onClick={afm.launch_folder_picker}>
                                    Path: {this.state.save_folder}
                                </div>
                                <TextInput name="File name base"
                                        notify_signal={scanner.base_file_name_changed}
                                        get_value={scanner.base_file_name}
                                        set_value={scanner.set_base_file_name} />
                            </div>
                            <button className="action-button save-button flex-no-resize" onClick={this.save_data} disabled={this.state.scanning}>{this.state.data_saved? "Save (✓)": "Save "}</button>
                        </div>
                        <div className="save-row justify-space-between">
                            <label className="checkbox"><input type="checkbox" onChange={this.handle_auto_save_change} checked={this.state.auto_save}/> Auto-Save</label>
                            <label className="checkbox"><input type="checkbox" onChange={this.handle_continuous_scan_change} checked={this.state.continuous_scan}/> Continuous Scan</label>
                            <label className="checkbox"><input type="checkbox" onChange={this.handle_save_png_change} checked={this.state.save_png}/> Save PNG</label>
                        </div>
                        <Dropdown options_list={[
                                    {text: "gsf", cmd_number: 0},
                                    {text: "tsv", cmd_number: 1},
                                ]}
                                selection_method={scanner.set_save_format}
                                notify_signal={scanner.save_format_changed}
                                get_value={scanner.save_format}
                                title="Save format"/>
                        <div className="save-message overflow-hidden flex-no-resize"><span className="roboto-medium">{this.state.save_message}</span><span>&nbsp;</span></div>
                        <div className="top-row">
                            <button className="action-button" onClick={this.state.scanning ? this.pause_scanning : this.start_or_resume_scanning}>{this.state.scanning ? "Pause" : (this.state.starting_fresh_scan ? "Scan" : "Resume")}</button>
                            <button className="action-button" onClick={this.clear_scan}>Reset</button>
                            <button className="action-button" onClick={this.reset_zoom} disabled={!this.state.zoom_set}>Reset Zoom</button>
                        </div>
                        <p className="advanced-controls-toggle" onClick={this.toggle_advanced_controls}><span>{this.state.advanced ? "Hide" : "Show"}</span> Advanced Controls</p>
                        <div className={(this.state.advanced ? "visible" : "hidden") + " " + "top-row"}>
                            <InlineScanControls />
                            <button className="action-button" onClick={this.eliminate_outliers} disabled={this.state.scanning || !this.state.starting_fresh_scan}>Clean</button>
                            <label id="use_level_checkbox"><input type="checkbox" onChange={this.handle_level_change} checked={this.state.use_level}/>Level Image</label>
                        </div>
                    </div>
                </div>
                )
        },
    });
    return Scan;
});
