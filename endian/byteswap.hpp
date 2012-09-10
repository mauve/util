/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */
#ifndef __UTIL_ENDIAN__BYTESWAP_HPP__
#define __UTIL_ENDIAN__BYTESWAP_HPP__

#include <boost/cstdint.hpp>

namespace endian {

// public interface here:

template <typename T>
void byte_swap_inplace (T& val);

template <typename T>
T byte_swap (const T& val);


// implementation

namespace swappers {

template <typename T>
struct byte_swapper
{
	// do not implement, SPECIALIZE

	static void swap_inplace (T& value);
	static T swap (const T value);
};

template <>
struct byte_swapper<boost::int8_t>
{
	static inline void swap_inplace (boost::int8_t value)
	{}

	static inline boost::int8_t swap(boost::int8_t value)
	{
		return value;
	}
};

template <>
struct byte_swapper<boost::uint8_t>
{
	static inline void swap_inplace (boost::uint8_t value)
	{}

	static inline boost::uint8_t swap(boost::uint8_t value)
	{
		return value;
	}
};

template <>
struct byte_swapper<boost::int16_t>
{
	static inline void swap_inplace (boost::int16_t& value)
	{
		value = (boost::int16_t)((boost::uint16_t(value) >> 8) | (boost::uint16_t(value) << 8));
	}

	static inline boost::int16_t swap (boost::int16_t value)
	{
		swap_inplace (value);
		return value;
	}
};

template <>
struct byte_swapper<boost::uint16_t>
{
	static inline void swap_inplace (boost::uint16_t& value)
	{
		value = (boost::uint16_t)((boost::uint16_t(value) >> 8) | (boost::uint16_t(value) << 8));
	}

	static inline boost::uint16_t swap (boost::uint16_t value)
	{
		swap_inplace (value);
		return value;
	}
};

template <>
struct byte_swapper<boost::int32_t>
{
	static inline boost::int32_t swap (boost::uint32_t val)
	{
        return ((((val) & 0xff000000u) >> 24) |
                (((val) & 0x00ff0000u) >>  8) |
                (((val) & 0x0000ff00u) <<  8) |
                (((val) & 0x000000ffu) << 24));
	}

	static inline void swap_inplace (boost::int32_t& val)
	{
		val = swap(val);
	}
};

template <>
struct byte_swapper<boost::uint32_t>
{
	static inline boost::uint32_t swap (boost::uint32_t val)
	{
        return ((((val) & 0xff000000u) >> 24) |
                (((val) & 0x00ff0000u) >>  8) |
                (((val) & 0x0000ff00u) <<  8) |
                (((val) & 0x000000ffu) << 24));
	}

	static inline void swap_inplace (boost::uint32_t& val)
	{
		val = swap(val);
	}
};

#ifndef BOOST_NO_INT64_T

template <>
struct byte_swapper<boost::int64_t>
{
	static inline boost::int64_t swap (boost::uint64_t val)
	{
        return ((((val) & 0xff00000000000000ull) >> 56) |
                (((val) & 0x00ff000000000000ull) >> 40) |
                (((val) & 0x0000ff0000000000ull) >> 24) |
                (((val) & 0x000000ff00000000ull) >> 8 ) |
                (((val) & 0x00000000ff000000ull) << 8 ) |
                (((val) & 0x0000000000ff0000ull) << 24) |
                (((val) & 0x000000000000ff00ull) << 40) |
                (((val) & 0x00000000000000ffull) << 56));
	}

	static inline void swap_inplace (boost::int64_t& val)
	{
		val = swap(val);
	}
};

template <>
struct byte_swapper<boost::uint64_t>
{
	static inline boost::uint64_t swap (boost::uint64_t val)
	{
        return ((((val) & 0xff00000000000000ull) >> 56) |
                (((val) & 0x00ff000000000000ull) >> 40) |
                (((val) & 0x0000ff0000000000ull) >> 24) |
                (((val) & 0x000000ff00000000ull) >> 8 ) |
                (((val) & 0x00000000ff000000ull) << 8 ) |
                (((val) & 0x0000000000ff0000ull) << 24) |
                (((val) & 0x000000000000ff00ull) << 40) |
                (((val) & 0x00000000000000ffull) << 56));
	}

	static inline void swap_inplace (boost::uint64_t& val)
	{
		val = swap(val);
	}
};

#endif // BOOST_NO_INT64_T

}  // namespace swappers

template <typename T>
void byte_swap_inplace (T& val)
{
	swappers::byte_swapper<T>::swap_inplace(val);
}

template <typename T>
T byte_swap (const T& val)
{
	return swappers::byte_swapper<T>::swap (val);
}

}  // namespace endian

#endif /* __UTIL_ENDIAN__BYTESWAP_HPP__ */
