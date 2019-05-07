#pragma once
#include <string>
#include "ImageDatabase.h"
#include "boost/property_tree/ptree.hpp"

namespace cubesat::telemetry
{
	/**
	 * Configuration data for a telemetry handler module.
	 * Setting #reporting_index and #reporting_doctype_name affects indices and names of files stored to Elasticsearch
	 * Setting #image_format and #image_frame_size specifies the expected format and number of packet fragments for
	 * images sent from the satellite.
	 */
	struct TelemetryConfig
	{
		std::string reporting_index;
		std::string reporting_doctype_name;
		uint32_t image_frame_size;
		database::ImageDatabase::format image_format;

		/**
		 * Returns a Telemetry Configuration object from a given boost property tree, \p telemetry_conf .
		 * The configuration must contain fields: "reporting doctype", "reporting index", "image size", and "image format".
		 */
		static TelemetryConfig from_config(boost::property_tree::ptree& telemetry_conf);
	};
}

