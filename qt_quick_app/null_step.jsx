 define(["jquery", "react",], function($, React) {
    var NullStep = React.createClass({
        componentWillReceiveProps : function(nextProps) {
            if (nextProps.showStep === false) {
                $('.null-wrapper').hide();
            } else {
                $('.null-wrapper').show();
            }
        },
        render: function() {
            return (
                <div className="wrapper null-wrapper"></div>
            )
        },
    });
    return NullStep;
});