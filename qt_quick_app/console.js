define([], function() {
	var log = console.log;
	console.log = function () {
	  main_window.log_cpp("js message: " + Array.prototype.slice.call(arguments));
	  log.apply(this, Array.prototype.slice.call(arguments));
	};
	return console;
});
