#pragma once
#include "server_http.hpp"
#include "TelemetryData.h"

/*
 * Some utility functions pertaining to the rockblock API. For more info see:
 * http://www.rock7mobile.com/downloads/RockBLOCK-Web-Services-User-Guide.pdf
 */
namespace cubesat::telemetry
{
	using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

	/**
	 * This function writes the required code 200 "OK" response required every time data is received from rockblock
	 * to \p response
	 */
	void write_rockblock_ok_response(HttpServer::Response& response);

	/**
	 * Reads a http parameter map \p params and returns a RockBlockReport object containing the API data
	 */
	RockBlockReport parse_rockblock_request_params(HttpServer::Request& params);
}