#include "ImageDatabase.h"

namespace cubesat::database
{
	void ImageDatabase::sort_image_files()
	{
		images.sort([](boost::filesystem::path & i1, boost::filesystem::path & i2)
		{
			return boost::filesystem::last_write_time(i1) > boost::filesystem::last_write_time(i2);
		});
	}
	
	std::string ImageDatabase::get_format_extension(ImageDatabase::format format)
	{
		switch (format)
		{
		case jpeg:
			return ".jpeg";
		case none:
			return "";
		default:
			return "";
		}
	}
	
	ImageDatabase::format ImageDatabase::get_format(std::string const& str_format)
	{
		if (str_format == "jpeg")
		{
			return ImageDatabase::format::jpeg;
		}
	
		return ImageDatabase::format::none;
	}
	
	ImageDatabase::ImageDatabase(boost::filesystem::path const& location) :
		db_directory(std::move(location))
	{
		if (!boost::filesystem::exists(db_directory))
		{
			boost::filesystem::create_directory(db_directory);
		}
	
		for (auto& image : boost::filesystem::directory_iterator(db_directory))
		{
			images.push_back(image);
		}
	
		sort_image_files();
	}
	
	void ImageDatabase::write_image(ImageData const& image)
	{
		auto const fname = db_directory / (image.name + get_format_extension(image.format));
	
		if (boost::filesystem::exists(fname))
		{
			throw std::invalid_argument("Image file with name \"" + fname.string() + "\" already exists");
		}
	
		std::fstream file;
		file.open(fname.string(), std::ios::app | std::ios::binary);
		file.write(reinterpret_cast<const char*>(image.binary.data()), image.binary.size());
		images.push_front(fname);
	
		std::cout << "Added image." << std::endl;
	
		for (auto& img : images)
		{
			std::cout << img.string() << std::endl;
		}
	}
}
