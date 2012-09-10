
#include <asio/buffer_queue.hpp>

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
	std::size_t remaining_size = i.data_current - i.data_buffer;
	return const_buffer(i.data_current, remaining_size);
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
		std::size_t remaining_size = i.data_current - i.data_buffer - bytes_transferred;
		i.callback(ec, i.size - remaining_size);
	}

	_queue.pop_front ();
}

void buffer_queue::cancel ()
{
	while (!empty())
		error(error_code(operation_canceled, generic_category()), 0);
}

}  // namespace asio

}  // namespace util



