/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <buffer/buffer_queue.hpp>

namespace util {

namespace asio {

using boost::asio::const_buffer;

using boost::system::error_code;

using boost::system::errc::success;
using boost::system::errc::operation_canceled;
using boost::system::generic_category;

buffer_queue::buffer_queue ()
{}

buffer_queue::~buffer_queue ()
{}

bool buffer_queue::empty () const
{
	return _queue.empty ();
}

const_buffer buffer_queue::peek () const
{
	if (empty())
		throw std::out_of_range("buffer queue empty");

	const item& i = _queue.front();
	return const_buffer(i.data_current, i.remaining());
}

bool buffer_queue::consume (std::size_t num_bytes)
{
	if (empty())
		return false;

	item& i = _queue.front();
	i.data_current += num_bytes;

	if (i.data_current >= (i.data_buffer + i.size)) {
		if (i.callback)
			i.callback(error_code(success, generic_category()), i.size);
		_queue.pop_front();
	}

	return !empty();
}

void buffer_queue::error (const error_code& ec,
		std::size_t bytes_transferred)
{
	if (empty())
		return;

	const item& i = _queue.front();
	if (i.callback) {
		i.callback(ec, i.consumed());
	}

	_queue.pop_front ();
}

void buffer_queue::cancel ()
{
	while (!empty())
		error(error_code(operation_canceled, generic_category()), 0);
}

buffer_queue::item::item (boost::asio::const_buffer bf, const callback_type& cb)
	: callback(cb),
	  data_buffer(boost::asio::buffer_cast<const char*>(bf)),
	  data_current(boost::asio::buffer_cast<const char*>(bf)),
	  size(boost::asio::buffer_size(bf))
{}

buffer_queue::item::~item ()
{}

std::size_t buffer_queue::item::remaining () const
{
	if (data_current >= data_buffer + size)
		return 0;
	return data_buffer + size - data_current;
}

std::size_t buffer_queue::item::consumed () const
{
	return data_current - data_buffer;
}

}  // namespace asio

}  // namespace util



