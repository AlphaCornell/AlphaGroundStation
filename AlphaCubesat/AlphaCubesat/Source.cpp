#include <iostream>
#include <string>
#include "server_http.hpp"
#include "boost/asio.hpp"
#include <fstream>
#include "ElasticsearchDatabase.h"
#include "TelemetryHandler.h"

/**
 * Main entry function initializes servers, database handles,
 * and web request modules, such as handlers for ping requests and telemetry data
 */
int main() 
{
	using namespace cubesat;
	using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

	database::ElasticsearchDatabase document_db("localhost", 9200);
	database::ImageDatabase image_db("image_db_folder_test");
	HttpServer server;

	telemetry::TelemetryHandler telemetry(
		telemetry::TelemetryConfig{"test_index", "test_type", 11, database::ImageDatabase::format::jpeg}, 
		document_db, 
		image_db);

	server.config.port = 8080;

	server.resource["^/telemetry$"]["POST"] = [&telemetry](auto res, auto req){telemetry.on_request(res, req);};
	server.resource["^/ping$"]["GET"] = [](auto res, auto req){ std::cout << "got ping" << std::endl; res->write("pong :D"); };

	server.start();

	return 0;
}