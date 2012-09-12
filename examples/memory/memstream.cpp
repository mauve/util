/**
 * @file
 *
 * @brief This file is a quick example on how to use util::memory::memory_output_stream
 *        and util::memory::memory_input_stream
 */

#include <memory/memstream.hpp>

#include <iostream>
#include <iomanip>
#include <boost/cstdint.hpp>

/*
 * A simple struct in order to demonstrate
 * overloading of operator<<() and operator>>().
 */
struct my_struct
{
	boost::uint8_t a;
	boost::uint16_t b;
};

/*
 * Overload operator<<() to ease insertion, this operator is defined
 * in the same namespace as my_struct.
 */
util::memory::memory_output_stream& operator<< (util::memory::memory_output_stream& mos, const my_struct& s)
{
	return mos << s.a << s.b;
}

/*
 * Overload operator>>() to ease extraction, this operator is defined
 * in the same namespace as my_struct.
 */
util::memory::memory_input_stream& operator>> (util::memory::memory_input_stream& mis, my_struct& s)
{
	return mis >> s.a >> s.b;
}

int main(int argc, char* argv[])
{
	/*
	 * Demonstrate memory_input_stream
	 */
	{
		const char* read_buffer = "\xAA\xBB\xBB\xCC\xCC\xCC\xCC";

		util::memory::memory_input_stream mis(read_buffer, 7);
		my_struct s;
		boost::uint32_t c;
		mis >> s >> c;

		std::cout << std::hex
			<< "s.a=" << (int)s.a << "\n"
			<< "s.b=" << s.b << "\n"
			<< "  c=" << c << std::endl; 
	}

	/*
	 * Demonstrate memory_output_stream
	 */
	{
		char write_buffer[7];

		my_struct s = { 0xAA, 0xBBBB };
		boost::uint32_t c = 0xCCCCCCCC;

		util::memory::memory_output_stream mos(write_buffer, 7);
		mos << s << c;

		std::cout << "buffer=";
		for (int i = 0; i < 7; i++)
		{
			std::cout << ((int)write_buffer[i] & 0xFF);
		}
		std::cout << std::endl;
	}
	

	return 0;
}