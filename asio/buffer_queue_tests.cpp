/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <boost/test/unit_test.hpp>
#include <boost/array.hpp>

#include <asio/buffer_queue.hpp>
#include <stdexcept>
#include <iostream>

using boost::asio::buffer_cast;
using boost::asio::buffer_size;

struct callback
{
	bool called;
	boost::system::error_code error_code;
	std::size_t bytes_transferred;

	callback ()
		: called(false)
	{}

	void operator() (const boost::system::error_code& ec, std::size_t nb)
	{
		called = true;
		error_code = ec;
		bytes_transferred = nb;
	}
};

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_SUITE(asio_tests)

BOOST_AUTO_TEST_SUITE(buffer_queue_tests)

BOOST_AUTO_TEST_CASE(create_invariant)
{
	asio::buffer_queue queue;
	BOOST_CHECK(queue.empty());
	BOOST_CHECK_THROW(queue.peek(), std::out_of_range);
	BOOST_CHECK(!queue.consume(1));
	BOOST_CHECK_NO_THROW(queue.cancel());
	BOOST_CHECK_NO_THROW(queue.error(boost::system::error_code(boost::system::errc::operation_canceled, boost::system::get_generic_category()), 1));
}

BOOST_AUTO_TEST_CASE(peek)
{
	asio::buffer_queue queue;
	boost::array<char, 5> buffer;

	callback cb;
	BOOST_CHECK_NO_THROW(queue.push_back(buffer, boost::ref(cb)));
	BOOST_CHECK(!queue.empty());

	boost::asio::const_buffer peeked_buffer;
	BOOST_CHECK_NO_THROW(peeked_buffer = queue.peek());
	BOOST_CHECK(buffer_cast<const char*>(peeked_buffer) == buffer.data());
	BOOST_CHECK(buffer_size(peeked_buffer) == buffer.size());
}

BOOST_AUTO_TEST_CASE(consume)
{
	asio::buffer_queue queue;
	boost::array<char, 5> buffer;

	callback cb;
	BOOST_CHECK_NO_THROW(queue.push_back(buffer, boost::ref(cb)));
	BOOST_CHECK(!queue.empty());

	BOOST_CHECK(queue.consume(2));
	BOOST_CHECK(!cb.called);

	boost::asio::const_buffer peeked_buffer;
	BOOST_CHECK_NO_THROW(peeked_buffer = queue.peek());
	BOOST_CHECK(buffer_cast<const char*>(peeked_buffer) == buffer.data() + 2);
	BOOST_CHECK(buffer_size(peeked_buffer) == buffer.size() - 2);

	BOOST_CHECK(!queue.consume(3));
	BOOST_CHECK(cb.called);
	BOOST_CHECK_EQUAL(cb.error_code, boost::system::error_code(0, boost::system::get_generic_category()));
	BOOST_CHECK_EQUAL(cb.bytes_transferred, 5);
	BOOST_CHECK(queue.empty());
}

BOOST_AUTO_TEST_SUITE_END() // buffer_queue_tests

BOOST_AUTO_TEST_SUITE_END() // asio_tests

BOOST_AUTO_TEST_SUITE_END() // util

