#include "TelemetryConfig.h"

namespace cubesat::telemetry
{
	TelemetryConfig TelemetryConfig::from_config(boost::property_tree::ptree& telemetry_conf)
	{
		TelemetryConfig config;
		config.reporting_doctype_name = telemetry_conf.get<std::string>("reporting doctype");
		config.reporting_index = telemetry_conf.get<std::string>("reporting index");
		config.image_frame_size = telemetry_conf.get<int>("image size");
		config.image_format = database::ImageDatabase::get_format(telemetry_conf.get<std::string>("image format"));
		return config;
	}
}
