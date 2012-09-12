/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

/**
 * @file
 *
 * Helpers for reading possibly unaligned PODs from raw memory.
 *
 * @example memory/read.cpp
 */

#ifndef __UTIL_MEMORY__READ_HPP__
#define __UTIL_MEMORY__READ_HPP__

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <cstring>

namespace util {

namespace memory {

/**
 * @brief Reads a POD of type T from the address pointed to by @a address offsetted by @a offset.
 *
 * @see memory/read.cpp
 */
template <typename T>
#ifdef DOCUMENTATION
T
#else
typename boost::enable_if< boost::is_pod<T>, T>::type
#endif
read_unaligned (const char* memory, std::size_t offset = 0)
{
	T result;
	std::memcpy(&result, memory + offset, sizeof(T));
	return result;
}

/**
 * @brief Reads a POD of type T from the address pointed to by @a address and then moves
 * the pointer past the T for further reading.
 */
template <typename T>
#ifdef DOCUMENTATION
T
#else
typename boost::enable_if< boost::is_pod<T>, T>::type
#endif
read_unaligned_stream (const char*& memory)
{
	T result;
	std::memcpy(&result, memory, sizeof(T));
	memory += sizeof(T);
	return result;
}

}  // namespace memory

}  // namespace util

#endif // __UTIL_MEMORY__READ_HPP__
