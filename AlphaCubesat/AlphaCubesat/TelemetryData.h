#pragma once
#include <string>
#include "boost/date_time.hpp"
#include "boost/property_tree/ptree.hpp"

namespace cubesat::telemetry
{
	/**
	 * contains the data sent by rockblock API when reporting. For more info see:
	 * http://www.rock7mobile.com/downloads/RockBLOCK-Web-Services-User-Guide.pdf
	 */
	struct RockBlockReport
	{
		std::string imei; // unique serial number of physical rockblock unit
		uint32_t momsn; //rockblock API message serial number
		boost::posix_time::ptime transmit_time; //time rockblock transmitted the message
		double iridium_latitude; //estimated latitude of satellite
		double iridium_longitude; //estimated longitude of satellite
		double iridium_cep; //estimated accuracy of latitude and longitude numbers (see RB docs)
		std::string hex_encoded_cubesat_data; //binary data sent by satellite, hex encoded as a string

		/**
		 * Returns a property tree containing this report's data
		 */
		boost::property_tree::ptree get_property_tree() const;
	};
}

