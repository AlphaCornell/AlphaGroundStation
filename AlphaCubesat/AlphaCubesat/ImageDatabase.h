#pragma once
#include <vector>
#include <list>
#include <fstream>
#include <iostream>
#include <boost/filesystem.hpp>
#include "boost/algorithm/string.hpp"

namespace cubesat::database
{
	/**
	 * A store for images on the local filesystem
	 */
	class ImageDatabase
	{
	public:
	
		enum format
		{
			jpeg, //satellite only supports jpeg rn
			none
		};
	
		struct ImageData
		{
			std::string name;
			ImageDatabase::format format;
			std::vector<unsigned char> binary;
		};

		/**
		 * returns a string file extension of the supplied format
		 */
		static std::string get_format_extension(ImageDatabase::format format);

		/**
		 * takes a string of the image format and returns the corresponding enum type
		 */
		static ImageDatabase::format get_format(std::string const& str_format);
	
	private:
		boost::filesystem::path db_directory;
		std::list<boost::filesystem::path> images;
	
		void sort_image_files();
	
	public:
		/**
		 * Create an image database in the supplied directory path \p location
		 */
		ImageDatabase(boost::filesystem::path const& location);

		/**
		 * Store an \p image in the database (on the local filesystem, in the directory specified for the database instance)
		 */
		void write_image(ImageData const& image);
	};
}

