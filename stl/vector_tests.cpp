/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <stl/vector.hpp>

#include <boost/test/unit_test.hpp>

using util::stl::create_vector;

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_SUITE(stl_vector)

BOOST_AUTO_TEST_CASE(create_vector_1)
{
	std::vector<int> vector = create_vector(1);
	BOOST_CHECK_EQUAL(vector.size(), 1);

	std::vector<int>::iterator iter = vector.begin();
	BOOST_CHECK_EQUAL(*iter++, 1);

	BOOST_CHECK(iter == vector.end());
}

BOOST_AUTO_TEST_CASE(create_vector_2)
{
	std::vector<int> vector = create_vector(1, 2);
	BOOST_CHECK_EQUAL(vector.size(), 2);

	std::vector<int>::iterator iter = vector.begin();
	BOOST_CHECK_EQUAL(*iter++, 1);
	BOOST_CHECK_EQUAL(*iter++, 2);

	BOOST_CHECK(iter == vector.end());
}

BOOST_AUTO_TEST_CASE(create_vector_3)
{
	std::vector<int> vector = create_vector(1, 2, 3);
	BOOST_CHECK_EQUAL(vector.size(), 3);

	std::vector<int>::iterator iter = vector.begin();
	BOOST_CHECK_EQUAL(*iter++, 1);
	BOOST_CHECK_EQUAL(*iter++, 2);
	BOOST_CHECK_EQUAL(*iter++, 3);

	BOOST_CHECK(iter == vector.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
