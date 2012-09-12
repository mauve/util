/**
 * @file
 *
 * @brief This file is a quick example on how to use util::memory::read_unaligned()
 *        and util::memory::read_unaligned_stream()
 *
 * @see util::memory::read_unaligned()
 * @see util::memory::read_unaligned_stream()
 */


#include <memory/read.hpp>

#include <iostream>
#include <iomanip>

#include <boost/cstdint.hpp>

/**
 * Example of offset-based extraction and stream-based extraction.
 */
int main (int argc, char* argv[])
{
	const char* buffer = "\xAA\xBB\xBB\xCC\xCC\xCC\xCC";

	/*
	 * Extract uint8, uint16 and uint32 from buffer using offsets.
	 */
	std::cout
		<< std::hex
		<< "  u8=" << (int)util::memory::read_unaligned<boost::uint8_t>(buffer) << "\n"
		<< " u16=" << util::memory::read_unaligned<boost::uint16_t>(buffer, 1) << "\n"
		<< " u32=" << util::memory::read_unaligned<boost::uint32_t>(buffer, 3) << "\n";

	const char* ptr = &buffer[0];

	/*
	 * Extract uint8, uint16 and uint32 from buffer using streamed interface
	 * which does not require the user to keep track of offsets.
	 */
	std::cout << std::hex;
	std::cout << "  u8=" << (int)util::memory::read_unaligned_stream<boost::uint8_t>(ptr) << "\n";
	std::cout << " u16=" << util::memory::read_unaligned_stream<boost::uint16_t>(ptr) << "\n";
	std::cout << " u32=" << util::memory::read_unaligned_stream<boost::uint32_t>(ptr) << "\n";

	return 0;
}
