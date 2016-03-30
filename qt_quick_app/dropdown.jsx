define(["react", "console", "underscore"], function(React, console, _) {
    var Dropdown = React.createClass({
        getInitialState: function() {
            return {text: "Select an option"};
        },
        componentDidMount: function() {
            $(this.refs.dropdown_content).hide();
            this.props.notify_signal.connect(this.update_value_from_backend_change);
        },
        handle_menu_click: function() {
            $(this.refs.dropdown_content).toggle();
        },
        handle_item_click: function(index) {
            this.setState({
                text: this.props.options_list[index].text
            });
            this.props.selection_method(this.props.options_list[index].cmd_number);
            $(this.refs.dropdown_content).toggle();
        },
        update_value_from_backend_change: function(value) {
            var option = $.grep(this.props.options_list, function(e){ return e.cmd_number == value; })[0];
            this.setState({text: option.text});
        },
        render: function() {
            return (
                <div className="dropdown">
                    <p style={{display: "inline"}}>{this.props.title}: </p>
                    <div style={{display: "inline"}}>
                        <span onClick={this.handle_menu_click} className="dropbtn">{this.state.text} &#8594;</span>
                        <div style={{display: "inline"}} ref="dropdown_content" className="dropdown-content">
                          {this.props.options_list.map(function(option, i) {
                            var boundClick = this.handle_item_click.bind(this, i);
                            return (
                              <DropdownOption onClick={boundClick} key={i} title={option.text} ref={'option' + i} />
                            );
                          }, this)}
                        </div>
                    </div>
                </div>
            );
        }
    });
    var DropdownOption = React.createClass({
        render: function() {
            return <span className="dropdown-option" onClick={this.props.onClick}>{this.props.title}</span>
        }   
    })
    return Dropdown;
});