require(['components/synced_chart'], function(chart) {
	var Sweep = function() {
		this.name = "Sweep";
		this.long_name = "Frequency Sweep";
		this.amplitude_chart = new chart();
		this.phase_chart = new chart();
	}
	var source = $("#some-template").html();
	var template = Handlebars.compile(source);
	$('body').append(template(data));
	return Sweep;
});