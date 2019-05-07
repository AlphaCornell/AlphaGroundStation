#include "Packet.h"
#include <string>
#include <stdexcept>

namespace cubesat::telemetry
{
	Packet::Packet(std::vector<unsigned char>&& bytes) :
		raw_data(bytes),
		bytes_read(0),
		bytes_written(bytes.size())
	{
	}

	Packet::Packet(uint32_t initial_size) :
		raw_data(initial_size),
		bytes_read(0),
		bytes_written(0)
	{
	}

	void Packet::expand(const uint32_t size)
	{
		if (raw_data.capacity() == 0)
		{
			raw_data.resize(size, 0);
		}
		else
		{
			const auto new_size = size + bytes_written;
			const auto cur_capacity = raw_data.capacity();
			auto new_capacity = cur_capacity;

			while (new_capacity < new_size)
			{
				new_capacity += cur_capacity;
			}

			raw_data.resize(new_capacity, 0);
		}
	}

	unsigned char* Packet::read_ptr()
	{
		return raw_data.data() + bytes_read;
	}

	unsigned char* Packet::write_ptr()
	{
		return raw_data.data() + bytes_written;
	}

	template <typename T>
	T Packet::read()
	{
		const unsigned int size = sizeof(T);

		if (size > available())
		{
			throw std::out_of_range("Read past end of packet");
		}

		T res = *reinterpret_cast<T*>(read_ptr());
		bytes_read += size;
		return res;
	}

	template <typename T>
	void Packet::write(T val)
	{
		const unsigned int size = sizeof(T);

		if (raw_data.capacity() < size + bytes_written)
		{
			expand(size);
		}

		*reinterpret_cast<T*>(write_ptr()) = val;
		bytes_written += size;
	}

	template int8_t Packet::read<int8_t>();
	template uint8_t Packet::read<uint8_t>();
	template int16_t Packet::read<int16_t>();
	template uint16_t Packet::read<uint16_t>();
	template int32_t Packet::read<int32_t>();
	template uint32_t Packet::read<uint32_t>();

	template void Packet::write<int8_t>(int8_t val);
	template void Packet::write<uint8_t>(uint8_t val);
	template void Packet::write<int16_t>(int16_t val);
	template void Packet::write<uint16_t>(uint16_t val);
	template void Packet::write<int32_t>(int32_t val);
	template void Packet::write<uint32_t>(uint32_t val);

	uint32_t Packet::available() const
	{
		return bytes_written - bytes_read;
	}

	void Packet::write_int8(int8_t val)
	{
		write<int8_t>(val);
	}

	void Packet::write_uint8(uint8_t val)
	{
		write<uint8_t>(val);
	}

	void Packet::write_int16(int16_t val)
	{
		write<int16_t>(val);
	}

	void Packet::write_uint16(uint16_t val)
	{
		write<uint16_t>(val);
	}

	void Packet::write_int32(int32_t val)
	{
		write<int32_t>(val);
	}

	void Packet::write_uint32(uint32_t val)
	{
		write<uint32_t>(val);
	}

	void Packet::write_bytes(std::vector<unsigned char>::iterator start, std::vector<unsigned char>::iterator end)
	{
		const auto size = end - start;

		if (raw_data.capacity() < size + bytes_written)
		{
			expand(size);
		}

		std::copy(start, end, write_ptr());
		bytes_written += size;
	}

	void Packet::write_bytes(std::vector<unsigned char>& src)
	{
		write_bytes(src.begin(), src.end());
	}

	int8_t Packet::read_int8()
	{
		return read<int8_t>();
	}

	uint8_t Packet::read_uint8()
	{
		return read<uint8_t>();
	}

	int16_t Packet::read_int16()
	{
		return read<int16_t>();
	}

	uint16_t Packet::read_uint16()
	{
		return read<uint16_t>();
	}

	int32_t Packet::read_int32()
	{
		return read<int32_t>();
	}

	uint32_t Packet::read_uint32()
	{
		return read<uint32_t>();
	}

	void Packet::read_bytes(std::vector<unsigned char>::iterator start, std::vector<unsigned char>::iterator end)
	{
		const auto size = end - start;

		if (size > available())
		{
			throw std::out_of_range("Read past end of packet");
		}

		std::copy(read_ptr(), read_ptr() + size, start);
		bytes_read += size;
	}

	std::vector<unsigned char> Packet::read_bytes(uint32_t length)
	{
		if (length > available())
		{
			throw std::out_of_range("Read past end of packet");
		}

		std::vector<unsigned char> ret(length);
		std::copy(read_ptr(), read_ptr() + length, ret.data());
		bytes_read += length;

		return ret;
	}

	uint32_t Packet::set_read_idx(uint32_t new_idx)
	{
		const auto old_idx = bytes_read;

		if (new_idx < 0 || new_idx > bytes_written)
		{
			throw std::out_of_range("Out of bounds reader index: " + std::to_string(new_idx));
		}

		bytes_read = new_idx;

		return old_idx;
	}

	uint32_t Packet::set_write_idx(uint32_t new_idx)
	{
		const auto old_idx = bytes_written;

		if (new_idx < 0 || new_idx > bytes_written)
		{
			throw std::out_of_range("Out of bounds writer index: " + std::to_string(new_idx));
		}

		bytes_written = new_idx;

		return old_idx;
	}

	uint32_t Packet::reset_read()
	{
		const auto old_idx = bytes_read;
		bytes_read = 0;
		return old_idx;
	}

	uint32_t Packet::reset_write()
	{
		const auto old_idx = bytes_written;
		bytes_written = 0;
		return old_idx;
	}
}

