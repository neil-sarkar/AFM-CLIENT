define(["react", "highcharts"], function(React, Highcharts){
  var x = function (Highcharts, chartType){
    var displayName = 'Highcharts' + chartType;
    var result = React.createClass({
      displayName: displayName,

      propTypes: {
        config: React.PropTypes.object.isRequired,
        isPureConfig: React.PropTypes.bool
      },

      renderChart: function (config){
        if (!config) {
          throw new Error('Config must be specified for the ' + displayName + ' component');
        }
        var chartConfig = config.chart;
        var chart = Object.assign(chartConfig);
        var container_object;
        Object.assign(container_object, config);
        container_object.chart = chart;
        container_object.renderTo = this.refs.chart;
        this.chart = new Highcharts[chartType](container_object);
      },

      shouldComponentUpdate(nextProps) {
        if (!this.props.isPureConfig || !(this.props.config === nextProps.config)) {
          this.renderChart(nextProps.config);
        }
        return true;
      },

      getChart: function (){
        if (!this.chart) {
          throw new Error('getChart() should not be called before the component is mounted');
        }
        return this.chart;
      },

      componentDidMount: function (){
        this.renderChart(this.props.config);
      },

      render: function (){
        var props = this.props;
        Object.assign(props, props);
        props.ref = 'chart';
        return <div props={props} />;
      }
    });

    result.Highcharts = Highcharts;
    return result;
  };
  return x;
});