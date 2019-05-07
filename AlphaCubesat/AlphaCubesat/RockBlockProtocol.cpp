#include "RockBlockProtocol.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>

namespace cubesat::telemetry
{
	void write_rockblock_ok_response(HttpServer::Response& response)
	{
		response.write("HTTP 200 OK\r\n");
	}

	RockBlockReport parse_rockblock_request_params(HttpServer::Request& params)
	{
		// Parse parameters out of post data string, which is URL encoded
		// Example: "param1=value1&param2=value%3awithSpecialCharacters"
		// becomes "param1 value, param2 value:withSpecialCharacters"

		auto req_str = params.content.string();
		boost::property_tree::ptree param_tree;
		std::vector<std::string> param_list;
		std::vector<std::string> param_args;

		boost::split(param_list, req_str, boost::is_any_of("&"));

		for (auto param : param_list)
		{
			param_args.clear();
			boost::replace_all(param, "%3A", ":");
			std::cout << param << std::endl;
			split(param_args, param, boost::is_any_of("="));
			param_tree.put(param_args[0], param_args[1]);
		}

		// Use the resulting property tree to actually get the data

		auto imei = param_tree.get_optional<std::string>("imei");
		auto momsn = param_tree.get_optional<uint32_t>("momsn");
		auto ttime = param_tree.get_optional<std::string>("transmit_time");
		auto lat = param_tree.get_optional<double>("iridium_latitude");
		auto lng = param_tree.get_optional<double>("iridium_longitude");
		auto cep = param_tree.get_optional<double>("iridium_cep");
		auto data = param_tree.get_optional<std::string>("data");

		if (imei && momsn && ttime && lat && lng && cep && data)
		{
			RockBlockReport res;
			res.imei = imei.get();
			res.momsn = momsn.get();
			res.transmit_time = boost::posix_time::time_from_string(ttime.get()); //TODO make sure locale is actually compatible with the boost conversion function
			res.iridium_latitude = lat.get();
			res.iridium_longitude = lng.get();
			res.iridium_cep = cep.get();
			res.hex_encoded_cubesat_data = data.get();
			return res;
		}

		throw std::invalid_argument("Malformed rockblock api request: " + req_str);
	}
}
