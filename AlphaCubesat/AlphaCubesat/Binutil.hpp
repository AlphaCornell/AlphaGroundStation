#pragma once
#include <stdexcept>
#include <vector>

namespace cubesat::binutil
{
	/**
	 * Convert character to integer value
	 */
	inline int char_to_int(char input)
	{
		if (input >= '0' && input <= '9')
			return input - '0';
		if (input >= 'A' && input <= 'F')
			return input - 'A' + 10;
		if (input >= 'a' && input <= 'f')
			return input - 'a' + 10;
		throw std::invalid_argument("Invalid input string");
	}
	
	/** 
	 * This function assumes src to be a zero terminated sanitized string with
	 * an even number of [0-9a-f] characters, and target to be sufficiently large
	 */
	inline void hex_to_bin(const char* src, unsigned char* target)
	{
		while (*src && src[1])
		{
			*(target++) = char_to_int(*src) * 16 + char_to_int(src[1]);
			src += 2;
		}
	}
	
	/**
	 * Convenience function - converts hex encoded string to byte array
	 * in a more C++-style way than the above methods
	 */
	inline std::vector<unsigned char> hex_str_to_bin(std::string const& encoded)
	{
		if (encoded.length() % 2 != 0)
		{
			throw std::invalid_argument("Bad hex string, must have even number of characters");
		}
	
		std::vector<unsigned char> binary(encoded.length() / 2);
		hex_to_bin(encoded.c_str(), binary.data());
		return binary;
	}
}
