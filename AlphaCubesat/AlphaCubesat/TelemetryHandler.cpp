#include "TelemetryHandler.h"
#include "RockBlockProtocol.h"

namespace cubesat::telemetry
{
	TelemetryHandler::TelemetryHandler(TelemetryConfig const& config, database::ElasticsearchDatabase& reporter, database::ImageDatabase& image_store) :
		config(config),
		reporter(reporter),
		image_store(image_store)
	{
	}

	void TelemetryHandler::on_request(std::shared_ptr<HttpServer::Response> response, std::shared_ptr<HttpServer::Request> request)
	{
		std::cout << "got request" << std::endl;
		//std::cout << request->content.string() << std::endl;

		try
		{
			auto report = parse_rockblock_request_params(*request);

			std::stringstream ss;
			write_json(ss, report.get_property_tree());

			std::cout << "Got Request. Printing contents..." << std::endl;
			std::cout << ss.str() << std::endl;
		} 
		catch(std::invalid_argument& e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}
		catch(std::exception& e)
		{
			std::cout << "error: " << e.what() << std::endl;
		}

		write_rockblock_ok_response(*response);
	}
}
