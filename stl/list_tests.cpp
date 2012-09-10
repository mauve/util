
#include <stl/list.hpp>

#include <boost/test/unit_test.hpp>

using util::stl::create_list;

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_SUITE(stl_list)

BOOST_AUTO_TEST_CASE(create_list_1)
{
	std::list<int> list = create_list(1);
	BOOST_CHECK_EQUAL(list.size(), 1);

	std::list<int>::iterator iter = list.begin();
	BOOST_CHECK_EQUAL(*iter++, 1);

	BOOST_CHECK(iter == list.end());
}

BOOST_AUTO_TEST_CASE(create_list_2)
{
	std::list<int> list = create_list(1, 2);
	BOOST_CHECK_EQUAL(list.size(), 2);

	std::list<int>::iterator iter = list.begin();
	BOOST_CHECK_EQUAL(*iter++, 1);
	BOOST_CHECK_EQUAL(*iter++, 2);

	BOOST_CHECK(iter == list.end());
}

BOOST_AUTO_TEST_CASE(create_list_3)
{
	std::list<int> list = create_list(1, 2, 3);
	BOOST_CHECK_EQUAL(list.size(), 3);

	std::list<int>::iterator iter = list.begin();
	BOOST_CHECK_EQUAL(*iter++, 1);
	BOOST_CHECK_EQUAL(*iter++, 2);
	BOOST_CHECK_EQUAL(*iter++, 3);

	BOOST_CHECK(iter == list.end());
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
