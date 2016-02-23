define(["react", "console", "underscore"], function(React, console, _) {
    var Dropdown = React.createClass({
        getInitialState: function() {
            return {
                text: "Select an option"
            };
        },
        componentDidMount: function() {
            $(this.refs.dropdown_content).hide();
        },
        handle_menu_click: function() {
            $(this.refs.dropdown_content).toggle();
        },
        handle_item_click: function(index) {
            this.setState({
                text: this.props.options_list[index]
            });
            
        },
        render: function() {
            console.log(this.props.options_list);
            return (
                <div className="dropdown">
                    <p onClick={this.handle_menu_click} className="dropbtn">{this.state.text}</p>
                    <div ref="dropdown_content" className="dropdown-content">
                      {this.props.options_list.map(function(option, i) {
                        var boundClick = this.handle_item_click.bind(this, i);
                        return (
                          <DropdownOption onClick={boundClick} key={i} title={option} ref={'option' + i} />
                        );
                      }, this)}
                    </div>
                </div>
            );
        }
    });
    var DropdownOption = React.createClass({
        render: function() {
            return <p onClick={this.props.onClick}>{this.props.title}</p>
        }   
    })
    return Dropdown;
});