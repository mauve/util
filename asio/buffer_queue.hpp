
#ifndef __UTIL_ASIO__BUFFER_QUEUE_HPP__
#define __UTIL_ASIO__BUFFER_QUEUE_HPP__

#include <deque>

#include <boost/function.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/noncopyable.hpp>
#include <boost/system/error_code.hpp>

namespace util {

namespace asio {

class buffer_queue :
	public boost::noncopyable
{
public:
	typedef boost::function<void (const boost::system::error_code&, std::size_t)> callback_type;

	buffer_queue ();
	~buffer_queue ();

	template <typename ConstBuffer>
	void push_back (ConstBuffer buffer, const callback_type& cb)
	{
		_queue.push_back(item (
				boost::asio::buffer_cast<const void*>(buffer),
				boost::asio::buffer_size(buffer),
				cb));
	}

	bool empty () const;

	boost::asio::const_buffer peek () const;

	bool consume (std::size_t num_bytes);

	void error (const boost::system::error_code& ec,
			std::size_t bytes_transferred);

	void cancel ();

private:
	struct item {
		item (const char* buffer, std::size_t size,
				const callback_type& cb);

		callback_type callback;
		const char* data_buffer;
		const char* data_current;
		std::size_t size;
	};

	std::deque<item> _queue;
};

}  // namespace asio

}  // namespace util


#endif /* __UTIL_ASIO__BUFFER_QUEUE_HPP__ */
