#include "RockBlock.h"

namespace cubesat::telemetry
{
	void write_rockblock_ok_response(HttpServer::Response& response)
	{
		response << "HTTP/1.1 200 OK";
	}
}
