/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <endian/byteswap.hpp>

#include <cstdlib>
#include <boost/test/unit_test.hpp>
#include <iomanip>

template <typename ValueType, typename CompareType>
void test_swapper(ValueType original, CompareType result)
{
	typedef util::endian::swappers::byte_swapper<ValueType> swapper;

	BOOST_CHECK_EQUAL(sizeof(ValueType), sizeof(CompareType));

	/*
	 * test swapper interface
	 */

	ValueType original_copy = original;
	swapper::swap_inplace(original_copy);

	BOOST_CHECK_MESSAGE(!std::memcmp(&original_copy, &result, sizeof(ValueType)),
		"  result: " << std::hex << result << " original_copy: " << std::hex << original_copy);

	original_copy = original;
	CompareType swapped = swapper::swap(original_copy);

	BOOST_CHECK_EQUAL(result, swapped);

	/*
	 * test public interface
	 */

	original_copy = original;
	util::endian::byte_swap_inplace(original_copy);

	BOOST_CHECK_MESSAGE(!std::memcmp(&original_copy, &result, sizeof(ValueType)),
		"  result: " << std::hex << result << " original_copy: " << std::hex << original_copy);

	original_copy = original;
	swapped = util::endian::byte_swap(original_copy);

	BOOST_CHECK_EQUAL(result, swapped);
	BOOST_CHECK_MESSAGE(!std::memcmp(&result, &swapped, sizeof(ValueType)),
		"  result: " << std::hex << result << " swapped: " << std::hex << swapped << " original_copy: " << std::hex << original_copy);
}

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_SUITE(byteswap_tests)

BOOST_AUTO_TEST_CASE(swap_int8_t)
{
	test_swapper<boost::int8_t, boost::uint8_t>(0x4B, 0x4B);
}

BOOST_AUTO_TEST_CASE(swap_uint8_t)
{
	test_swapper<boost::uint8_t, boost::uint8_t>(0xAB, 0xAB);
}

BOOST_AUTO_TEST_CASE(swap_int16_t)
{
	test_swapper<boost::int16_t, boost::int16_t>(0x1234, 0x3412);
	// todo add some test for negative values
}

BOOST_AUTO_TEST_CASE(swap_uint16_t)
{
	test_swapper<boost::uint16_t, boost::uint16_t>(0x1234, 0x3412);
}

BOOST_AUTO_TEST_CASE(swap_int32_t)
{
	test_swapper<boost::int32_t, boost::uint32_t>(0x12345678, 0x78563412);
	// todo add some test for negative values
}

BOOST_AUTO_TEST_CASE(swap_uint32_t)
{
	test_swapper<boost::uint32_t, boost::uint32_t>(0x12345678, 0x78563412);
}

#ifndef BOOST_NO_INT64_T

BOOST_AUTO_TEST_CASE(swap_int64_t)
{
	test_swapper<boost::int64_t, boost::uint64_t>(0x1234567890abcdefLL, 0xefcdab9078563412LL);
	// todo add some test for negative values
}

BOOST_AUTO_TEST_CASE(swap_uint64_t)
{
	test_swapper<boost::uint64_t, boost::uint64_t>(0x1234567890abcdefULL, 0xefcdab9078563412ULL);
	// todo add some test for negative values
}

#endif // !BOOST_NO_INT64_T

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
