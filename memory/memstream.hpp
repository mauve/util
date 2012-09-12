/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

/**
 * @file
 *
 * @brief Classes which makes it easier to read and write several PODs
 *        from a raw memory buffer.
 *
 * @example memory/memstream.cpp
 */

#ifndef UTIL_MEMSTREAM_HPP_
#define UTIL_MEMSTREAM_HPP_

#include <cstddef>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_pod.hpp>

namespace util {

namespace memory {

/**
 * @brief Write PODs to a raw memory buffer.
 *
 * @see operator<<(memory_output_stream&, const T&)
 */
class memory_output_stream
{
public:
	/**
	 * @brief Initializes the stream with the buffer starting at @a data and
	 *        ending at @a data + @a size.
	 *
	 * @note The buffer is not copied and must be kept valid during the
	 *       lifetime of the memory_output_stream.
	 */
	memory_output_stream (char* data, std::size_t size);

	/** Returns the number of bytes remaining in the stream. */
	std::size_t remains () const;

	/**
	 * @brief Copy the data from @a data with length @a length into the
	 *        stream at the current position.
	 *
	 * Copies the data from the buffer [@a data, @a data + @a length) into
	 * the stream at the streams current position. If the remaining space
	 * in the stream is less than @a length an exception is thrown and the
	 * stream is not modified.
	 *
	 * @exception std::out_of_range The remaining space is less than @a length.
	 */
	void write (const char* data, std::size_t length);

private:
	char* _begin;
	char* _current;
	char* _end;
};

/**
 * @brief Overloaded operator<<
 *
 * Calls memory_output_stream::write() on the object @a mos with address of
 * @a v and length set to @a sizeof(T). This function is not available for
 * types which the expression boost::is_pod<T> is false. In C++03 you must
 * specialize boost::is_pod<T> for user-defined PODs. You can overload this
 * function for your own types which are not PODs but which you want to
 * be streamable.
 *
 * @exception std::out_of_range The remaining space is less than @a sizeof(T)
 */
template <typename T>
#ifdef DOCUMENTATION
memory_output_stream&
#else
inline typename boost::enable_if<
	boost::is_pod<T>,
	memory_output_stream&
>::type
#endif
operator<< (memory_output_stream& mos, const T& v)
{
	mos.write ((const char*)&v, sizeof(v));
	return mos;
}

/**
 * @brief Extracts PODs from raw memory buffer.
 *
 * @see operator>>(memory_input_stream&, T&)
 */
class memory_input_stream
{
public:
	/**
	 * @brief Initializes the stream with the buffer starting at @a data and
	 *        ending at @a data + @a size.
	 *
	 * @note The buffer is not copied and must be kept valid during the
	 *       lifetime of the memory_input_stream.
	 */
	memory_input_stream (const char* data, std::size_t size);

	/** Returns the number of bytes remaining to be extracted from the stream. */
	std::size_t remains () const;

	/**
	 * @brief Copies @a length number of bytes from the stream's current position
	 *        into the buffer @a data.
	 *
	 * Copies @a length number of bytes from the stream's current position
	 * into the buffer [@a data, @a data + @a length) if the number of bytes
	 * remaining in the stream is less than @a length an exception is thrown
	 * and the stream is not modified.
	 *
	 * @exception std::out_of_range The remaining bytes in the stream is less than @a length.
	 */
	void read (char* data, std::size_t length);

	/**
	 * @brief Reserves @a length number of bytes in the stream.
	 *
	 * Reserves @a length number of bytes in the stream for manual extraction. This
	 * operation moves the streams current position forward by @a length bytes and
	 * returns the position in the stream before it was called.
	 *
	 * This enables extraction from the stream without copying the data, as the
	 * returned pointer can be cast to a suitable type and read directly. The returned
	 * address is not necessarily aligned so casting to a type with alignment
	 * requirements must be done with care, if unsure use extract() instead.
	 *
	 * If the number of remaining bytes in the stream is less than @a length
	 * an exception is thrown and the streams state is not modified.
	 *
	 * @returns The streams position before the reserve operation.
	 *
	 * @exception std::out_of_range The remaining bytes in the stream is less than @a length.
	 */
	const char* reserve (std::size_t length);

	/**
	 * @brief Extracts a POD from the stream
	 *
	 * Extract a POD from the stream and returns and at the same
	 * time taking care of alignment requirements.
	 *
	 * If the number of remaining bytes in the stream is less than @a length
	 * an exception is thrown and the streams state is not modified.
	 *
	 * @returns Returns the extracted POD.
	 *
	 * @exception std::out_of_range The remaining bytes in the stream is less than @a sizeof(T)
	 */
#ifdef DOCUMENTATION
	T
#else
	template <typename T>
	inline typename boost::enable_if<
		boost::is_pod<T>,
		T
	>::type
#endif
	extract ()
	{
		T v;
		read ((char*)&v, sizeof(T));
		return v;
	}

private:
	const char* _begin;
	const char* _current;
	const char* _end;
};

/**
 * Blah
 */
template <typename T>
#ifdef DOCUMENTATION
memory_input_stream&
#else
inline typename boost::enable_if<
	boost::is_pod<T>,
	memory_input_stream&
>::type
#endif
operator>> (memory_input_stream& mis, T& v)
{
	mis.read((char*)&v, sizeof(v));
	return mis;
}

}  // namespace memory

}  // namespace util

#endif /* UTIL_MEMSTREAM_HPP_ */
