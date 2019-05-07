#pragma once
#include <vector>
#include <cstdint>

namespace cubesat::telemetry
{
	/**
	 * Provides facilities for reading and writing primitive types
	 * to buffers of binary data, such as basic numeric types, or other buffers.
	 * Uses std::vector<unsigned char> as underlying buffer implementation,
	 * and maintains a reading and writing index as data is read/written linearly
	 * in the buffer.
	 */
	class Packet
	{
	private:
		std::vector<unsigned char> raw_data;
		uint32_t bytes_read;
		uint32_t bytes_written;

		template <typename T> T read();
		template <typename T> void write(T val);
		void expand(uint32_t size);
		unsigned char* read_ptr();
		unsigned char* write_ptr();

	public:
		Packet(std::vector<unsigned char>&& bytes);
		Packet(uint32_t initial_size = 0);

		Packet() = delete;
		Packet(Packet& other) = delete;
		Packet(Packet&& other) = delete;
		~Packet() = default;

		void operator=(Packet& other) = delete;
		void operator=(Packet&& other) = delete;

		/**
		 * Returns the number of bytes that can still be read
		 */
		uint32_t available() const;

		void write_int8(int8_t val);
		void write_uint8(uint8_t val);
		void write_int16(int16_t val);
		void write_uint16(uint16_t val);
		void write_int32(int32_t val);
		void write_uint32(uint32_t val);
		void write_bytes(std::vector<unsigned char>::iterator start, std::vector<unsigned char>::iterator end);
		void write_bytes(std::vector<unsigned char>& src);

		int8_t read_int8();
		uint8_t read_uint8();
		int16_t read_int16();
		uint16_t read_uint16();
		int32_t read_int32();
		uint32_t read_uint32();
		void read_bytes(std::vector<unsigned char>::iterator start, std::vector<unsigned char>::iterator end);
		std::vector<unsigned char> read_bytes(uint32_t length);

		/**
		 * Sets the reading index within the underlying buffer, from which future data is read
		 */
		uint32_t set_read_idx(uint32_t new_idx);

		/**
		 * Sets the writing index within the underlying buffer, to which future data is written
		 */
		uint32_t set_write_idx(uint32_t new_idx);

		/**
		 * Sets the reading index within the underlying buffer to zero
		 */
		uint32_t reset_read();

		/**
		 * Sets the writing index within the underlying buffer to zero
		 */
		uint32_t reset_write();
	};
}


