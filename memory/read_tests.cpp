
#include "read.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_SUITE(memory_tests)

BOOST_AUTO_TEST_CASE(read_unaligned)
{
	const unsigned char buffer[] = { 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00 };

	BOOST_CHECK_EQUAL(0xFFFFFFFF, memory::read_unaligned<boost::uint32_t>(buffer, 1));
}

BOOST_AUTO_TEST_CASE(read_unaligned_stream)
{
	const unsigned char buffer[] = { 0xFF, 0xFF, 0xBB, 0xBB };

	const char* cursor = buffer;
	BOOST_CHECK_EQUAL(0xFFFF, memory::read_unaligned_stream<boost::uint16_t>(cursor));
	BOOST_CHECK_EQUAL(0xBBBB, memory::read_unaligned_stream<boost::uint16_t>(cursor));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()


