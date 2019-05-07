#pragma once
#include "TelemetryConfig.h"
#include "ElasticsearchDatabase.h"
#include "server_http.hpp"
#include "boost/property_tree/json_parser.hpp"

namespace cubesat::telemetry
{
	using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

	/**
	 * Http "module" that handles telemetry data, received from the RockBlock API
	 * This module receives data, then processes the raw binary sent by a satellite,
	 * then archives the data to the given elasticsearch database and image store
	 */
	class TelemetryHandler
	{
	private:
		TelemetryConfig config;
		database::ElasticsearchDatabase& reporter;
		database::ImageDatabase& image_store;

	public:
		TelemetryHandler() = delete;
		~TelemetryHandler() = default;

		TelemetryHandler(TelemetryConfig const& config, database::ElasticsearchDatabase& reporter, database::ImageDatabase& image_store);

		/**
		 * Handles http \p request; receives, processes RockBlock API data
		 */
		void on_request(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request);
	};
}