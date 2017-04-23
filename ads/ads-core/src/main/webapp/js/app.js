(function() {

	var app = angular.module("myApp", []);

	app.controller("MethodController", [ '$http', function($http) {

		var controller = this;

		controller.formData = [];

		controller.status = 0;
		controller.hits = 0;
		
		controller.loading = false;
		controller.nlpOptions = [];
		controller.searchOptions = [];

		controller.methods = [];

		this.search = function(q, n, o) {
			$http({
				url : "./api/java/methods/scenarios",
				method : "GET",
				params : {
					input : controller.formData.query,
					nlp : controller.formData.nlp,
					options : controller.formData.options
				}
			}).success(function(data, status, headers, config) {
				controller.status = status;
				controller.hits = data.count;
				controller.methods = data.items;
			}).error(function(data, status, headers, config) {
				controller.status = status;
			});
		};

		this.loadOptions = function() {
			controller.loading = true;
			$http({
				url : "./api/java/methods/scenarios/nlp",
				method : "GET",
			}).success(function(data, status, headers, config) {
				controller.nlpOptions = data.items;
			});
			$http({
				url : "./api/java/methods/scenarios/search",
				method : "GET",
			}).success(function(data, status, headers, config) {
				controller.searchOptions = data.items;
			});
		};

	} ]);

})();