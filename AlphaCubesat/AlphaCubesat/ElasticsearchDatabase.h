#pragma once
#include <string>
#include <iostream>
#include "client_http.hpp"
#include "boost/optional.hpp"
#include "boost/date_time.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

namespace cubesat::database
{
	/**
	 * An Elasticsearch database accessor used for submitting requests
	 * to the given database with json data. Automatically appends local date and time
	 * to index name to create an index pattern for sorting data. Note that this is not the actual
	 * timestamp information of any contained data.
	 */
	class ElasticsearchDatabase
	{
	private:
		std::string endpoint;
	
		std::string build_full_index_path(std::string const& index_base_name, std::string const& document_type, boost::optional<uint64_t> const& doc_id) const;
	
	public:
		/**
		 * Create a database representation that connects to elasticsearch using the provided ip and port
		 */
		ElasticsearchDatabase(std::string const& pHost, int pPort);
	
		ElasticsearchDatabase() = delete;
		ElasticsearchDatabase(ElasticsearchDatabase const& other) = delete;
		ElasticsearchDatabase(ElasticsearchDatabase const&& other) = delete;
		void operator=(ElasticsearchDatabase const& other) = delete;
		void operator=(ElasticsearchDatabase const&& other) = delete;
		~ElasticsearchDatabase() = default;

		/**
		 *	Indexes a document synchronously, using \p index_base_name appended with local date for the index, \p document_type as the doc type,
		 *	an optional document uid/serial number (if none is provided, elasticsearch generates one. This is the recommended approach),
		 *	and json data as a string to be inserted into the database.
		 *	
		 *	Example usage:
		 *	A call to index("test_index", "test_type", {}, "{\"time\" : \"2019-03-16T11:45:50+02:00\", \"value\" : 28.577}");
		 *	Will insert into the index test_index-<current time> a document of test_type, with json content: { "time" : "2019-03-16T11:45:50+02:0", "value" : 28.577 }
		 *	
		 *	A note to future maintainers: document types will be deprecated in upcoming versions of elasticsearch - to ensure best compatibility,
		 *	only use one type per index, or rework this function in the future to no longer accept document types.
		 */
		void index(std::string const& index_base_name, std::string const& document_type, boost::optional<uint64_t> const& doc_id, std::string const& data_json);
	};
}


