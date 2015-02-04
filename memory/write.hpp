/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

/**
 * @file
 *
 * Helpers for writing possibly unaligned PODs from raw memory.
 *
 * The functions do no bounds-checking, use memstream instead.
 * 
 */

#ifndef __UTIL_MEMORY__WRITE_HPP__
#define __UTIL_MEMORY__WRITE_HPP__

#include <boost/cstdint.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <cstring>

namespace util {

namespace memory {

/**
 * @brief Writes a POD of type T to the address pointed to by @a address
 *
 * @returns Returns the address directly after the last write
 *
 * @see memory/write.cpp
 */
template <typename T>
#ifdef DOCUMENTATION
boost::uint8_t*
#else
typename boost::enable_if< boost::is_pod<T>, boost::uint8_t*>::type
#endif
write (boost::uint8_t* memory, const T& value)
{
	std::memcpy(memory, &value, sizeof(T));
	return memory + sizeof(T);
}

/**
 * @brief Writes a POD of type T to the address pointed to by @a address and then moves
 * the pointer past the T for further writing.
 */
template <typename T>
#ifdef DOCUMENTATION
void
#else
typename boost::enable_if< boost::is_pod<T> >::type
#endif
write_stream (boost::uint8_t*& memory, const T& value)
{
	memory += write(memory, value);
}

}  // namespace memory

}  // namespace util

#endif // __UTIL_MEMORY__READ_HPP__
