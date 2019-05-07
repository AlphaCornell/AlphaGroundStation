#include "ElasticsearchDatabase.h"

namespace cubesat::database
{
	ElasticsearchDatabase::ElasticsearchDatabase(std::string const& pHost, int pPort) :
		endpoint(pHost + ":" + std::to_string(pPort))
	{
	}
	
	std::string ElasticsearchDatabase::build_full_index_path(std::string const& index_base_name, std::string const& document_type, boost::optional<uint64_t> const& doc_id) const
	{
		boost::posix_time::ptime timeLocal = boost::posix_time::second_clock::local_time();
		boost::gregorian::date date = timeLocal.date();
		// note this is not the actual time used in the data, 
		// it's just the local date of the ground station used for elasticsearch indexing purposes
		std::string const index_postfix =
			std::to_string(date.year()) + "."
			+ std::to_string(date.month()) + "."
			+ std::to_string(date.day());
	
		std::stringstream path;
	
		path << "/"
			 << index_base_name << "-" << index_postfix << "/"
			 << document_type << "/";
	
		if (doc_id)
		{
			path << std::to_string(doc_id.get());
		}
	
		return std::move(path.str());
	}
	
	void ElasticsearchDatabase::index(std::string const& index_base_name, std::string const& document_type, boost::optional<uint64_t> const& doc_id, std::string const& data_json)
	{
		using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;
		using HeaderMap = SimpleWeb::CaseInsensitiveMultimap;
	
		HttpClient elastic(endpoint);
		HeaderMap headers;
	
		headers.emplace("Content-Type", "application/json");
		std::string const path = build_full_index_path(index_base_name, document_type, doc_id);
	
		try
		{
			auto response = elastic.request("POST", path, data_json, headers);
			std::cout << "Got response from ES: " << response->content.string() << std::endl;
		}
		catch (const SimpleWeb::system_error & e)
		{
			std::cout << "Posting to ES resulted in error: " << e.what() << std::endl;
		}
	}
}
