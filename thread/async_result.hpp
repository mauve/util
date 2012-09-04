
#ifndef UTIL_THREAD_ASYNC_RESULT_HPP_
#define UTIL_THREAD_ASYNC_RESULT_HPP_

#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/system/error_code.hpp>
#include <boost/function.hpp>

namespace util {

namespace thread {

namespace detail {

	template <typename T>
	struct async_result_holder
	{
		typedef T value_type;
		typedef boost::function<void (value_type&)> completed_callback_type;
		typedef boost::function<void (const boost::system::error_code&)> error_callback_type;

		boost::mutex mutex;
		completed_callback_type completed_handler;
		error_callback_type error_handler;
		bool started;
		bool finished;
		boost::scoped_ptr<value_type> value_ptr;
		boost::system::error_code error;

		~async_result_holder ()
		{
			complete (boost::system::errc::operation_canceled);
		}

		void set_error_handler (const error_callback_type& handler)
		{
			boost::lock_guard<boost::mutex> lock(mutex);
			error_handler = handler;
		}

		void set_completed_handler (const completed_callback_type& handler)
		{
			boost::lock_guard<boost::mutex> lock(mutex);
			completed_handler = handler;
		}

		void complete (const boost::system::error_code& err)
		{
			boost::lock_guard<boost::mutex> lock(mutex);
			if (finished)
				return;
			finished = true;
			if (!started) {
				error = err;
			} else if (error_handler) {
				error_handler (err);
			}
		}

		void complete (const value_type& value)
		{
			boost::lock_guard<boost::mutex> lock(mutex);
			if (finished)
				return;
			finished = true;
			if (!started) {
				value_ptr.reset(new value_type(value));
			} else if (completed_handler) {
				completed_handler(value);
			}
		}

		void start ()
		{
			boost::lock_guard<boost::mutex> lock(mutex);
			if (started)
				return;
			started = true;
			if (finished) {
				if (value_ptr) {
					if (completed_handler)
						completed_handler(*value_ptr);
				} else {
					if (error_handler)
						error_handler(error);
				}
			}
		}
	};

}  // namespace detail

template <typename T>
class async_result
{
	typedef detail::async_result_holder<T> holder_type;
	typedef boost::shared_ptr<holder_type> storage_type;

public:
	typedef typename holder_type::value_type value_type;
	typedef typename holder_type::completed_callback_type completed_callback_type;
	typedef typename holder_type::error_callback_type error_callback_type;

	async_result ()
		: _storage(new holder_type)
	{}

	void set_error_handler (const error_callback_type& handler)
	{
		_storage->set_error_handler(handler);
	}

	void set_completed_handler (const completed_callback_type& handler)
	{
		_storage->set_completed_handler(handler);
	}

	void start ()
	{
		_storage->start();
	}

	void complete (const boost::system::error_code& error)
	{
		_storage->complete(error);
	}

	void complete (const value_type& value)
	{
		_storage->complete(value);
	}

	void cancel ()
	{
		_storage->complete (boost::system::errc::operation_canceled);
	}

private:
	storage_type _storage;
};

}  // namespace thread

}  // namespace util

#endif /* UTIL_THREAD_ASYNC_RESULT_HPP_ */
