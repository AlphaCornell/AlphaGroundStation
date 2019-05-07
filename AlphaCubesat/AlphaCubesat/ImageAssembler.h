#pragma once
#include <unordered_map>
#include <boost/optional.hpp>
#include <vector>

namespace cubesat::telemetry
{
	/**
	 * Accumulates multiple binary data fragments and assembles them into a single
	 * binary blob containing image data
	 */
	class ImageAssembler
	{
	private:
		std::vector<boost::optional<std::vector<unsigned char>>> image_fragments;

	public:
		ImageAssembler(uint32_t num_frags);
		~ImageAssembler() = default;

		/**
		 * Adds an image fragment to be accumulated into a full image.
		 * \p fragment is the index of the particular fragment being registered (where in
		 * the sequence of fragments that form the image).
		 * \p binary_data contains the raw data, which is *moved* into the assembler.
		 */
		void register_fragment(uint32_t fragment, std::vector<unsigned char>&& binary_data);

		/**
		 * Returns whether num_frags, the expected number of fragments for a full image, have been collected
		 */
		bool is_full();

		/**
		 * Returns whether num_frags, the expected number of fragments for a full image, have been collected
		 * If so, writes full image data to \p out_image_blob
		 */
		bool try_assemble_image(std::vector<unsigned char>& out_image_blob);
	};
}

