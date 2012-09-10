/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef __UTIL_ENDIAN_HPP__
#define __UTIL_ENDIAN_HPP__

#include <endian/byteswap.hpp>

#include <boost/call_traits.hpp>
#include <boost/detail/endian.hpp>

namespace endian {

template <typename T>
inline T to_network (T value)
{
#if defined(BOOST_BIG_ENDIAN)
	return value;
#elif defined(BOOST_LITTLE_ENDIAN)
	return swappers::byte_swapper<T>::swap(value);
#endif
}

template <typename T>
inline T to_host (T value)
{
#if defined(BOOST_BIG_ENDIAN)
	return value
#elif defined(BOOST_LITTLE_ENDIAN)
	return swappers::byte_swapper<T>::swap(value);
#endif
}

template <typename T>
inline void to_network_inplace (T& value)
{
#if defined(BOOST_LITTLE_ENDIAN)
	swappers::byte_swapper<T>::swap_inplace(value);
#endif
}

template <typename T>
inline void to_host_inplace (T& value)
{
#if defined(BOOST_LITTLE_ENDIAN)
	swappers::byte_swapper<T>::swap_inplace(value);
#endif
}

template <typename T>
inline T to_little (T value)
{
#if defined(BOOST_BIG_ENDIAN)
	return swappers::byte_swapper<T>::swap(value);
#elif defined(BOOST_LITTLE_ENDIAN)
	return value;
#endif
}

template <typename T>
inline T to_big (T value)
{
#if defined(BOOST_BIG_ENDIAN)
	return value;
#elif defined(BOOST_LITTLE_ENDIAN)
	return swappers::byte_swapper<T>::swap(value);
#endif
}

}  // namespace endian

#endif /* __UTIL_ENDIAN_HPP__ */
