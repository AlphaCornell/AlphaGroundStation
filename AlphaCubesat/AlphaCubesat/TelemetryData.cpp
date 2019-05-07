#include "TelemetryData.h"

namespace cubesat::telemetry
{
	boost::property_tree::ptree RockBlockReport::get_property_tree() const
	{
		boost::property_tree::ptree tree;
		tree.put("imei", imei);
		tree.put("momsn", momsn);
		tree.put("transmit_time", to_simple_string(transmit_time));
		tree.put("iridium_latitude", iridium_latitude);
		tree.put("iridium_longitude", iridium_longitude);
		tree.put("iridium_cep", iridium_cep);
		tree.put("hex_encoded_cubesat_data", hex_encoded_cubesat_data);
		return tree;
	}
}
