#include "ImageAssembler.h"
#include <string>

namespace cubesat::telemetry
{
	ImageAssembler::ImageAssembler(uint32_t num_frags) :
		image_fragments(num_frags)
	{
	}

	void ImageAssembler::register_fragment(uint32_t fragment, std::vector<unsigned char>&& binary_data)
	{
		if (fragment >= image_fragments.size())
		{
			throw std::out_of_range("Fragment number " + std::to_string(fragment) + " higher than total fragments for image");
		}

		image_fragments[fragment].emplace(binary_data);
	}

	bool ImageAssembler::is_full()
	{
		for (auto& p_frag : image_fragments)
		{
			if (!p_frag)
			{
				return false;
			}
		}

		return true;
	}

	bool ImageAssembler::try_assemble_image(std::vector<unsigned char> & out_image_blob)
	{
		if (!is_full())
			return false;

		out_image_blob.clear();

		for (auto& pblob : image_fragments)
		{
			//TODO copy more efficiently, but its not a huge deal. When the satellite only sends an image every few minutes, performance is unimportant
			auto& blob = pblob.value();
			for (auto& byte : blob)
			{
				out_image_blob.push_back(byte);
			}
		}

		return true;
	}
}

