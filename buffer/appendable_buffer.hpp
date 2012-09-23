/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

/**
 * @brief Defines a buffer which can be used to read large unknown buffers with Boost.Asio
 *
 * @note Unsure if this is required, I think boost::asio::streambuf does the same thing
 */

#ifndef UTIL_BUFFER_APPENDABLE_BUFFER_HPP_
#define UTIL_BUFFER_APPENDABLE_BUFFER_HPP_

#include <vector>
#include <boost/asio/buffer.hpp>

namespace util {

namespace buffer {

/**
 * @brief A buffer which makes it easier to receive large packets without knowing its size
 */
class appendable_buffer
{
public:
	/**
	 * @brief Creates an appendable_buffer and does not allocate any memory
	 *
	 * @post @a capacity() == @a 0
	 * @post @a filled_size() == @a 0
	 */
	appendable_buffer ();
	/**
	 * @brief Creates an appendable_buffer with the @a initial_size specified
	 *
	 * @post @a capacity() == @a initial_size
	 * @post @a filled_size() == @a 0
	 */
	explicit appendable_buffer (std::size_t initial_size);

	/** @brief Returns the total number of bytes available */
	std::size_t capacity () const;
	/** @brief Returns the number of bytes filled */
	std::size_t filled_size () const;
	
	/**
	 * @brief Clears the buffer and deallocates memory
	 *
	 * @post @a capacity() == @a 0
	 * @post @a filled_size() == @a 0
	 */
	void reset ();

	/**
	 * @brief Moves the content to the specified std::vector<char>
	 *
	 *
	 * @post @a capacity() == @a 0
	 * @post @a filled_size() == @a 0
	 */
	void move_to (std::vector<char>& result);

	/** @brief Returns a pointer to the first byte */
	const char* begin () const;
	/** @brief Returns a pointer past the last byte with data in it */
	const char* end () const;

	/** @brief Returns a mutable buffer of size @a buf_size */
	boost::asio::mutable_buffers_1 get_appendable_buffer (std::size_t buf_size);
	void report_appended (std::size_t num_filled);

private:
	std::vector<char> _buffer;
	std::size_t _filled_size;
};

}  // namespace buffer

}  // namespace util

#endif /* UTIL_BUFFER_APPENDABLE_BUFFER_HPP_ */
