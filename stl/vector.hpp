/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_STL_VECTOR_HPP_
#define UTIL_STL_VECTOR_HPP_

#include <vector>

namespace util {

namespace stl {

template <typename T>
inline std::vector<T> create_vector(const T& v)
{
	return std::vector<T>(1, v);
}

template <typename T>
inline std::vector<T> create_vector(const T& a, const T& b)
{
	std::vector<T> ret(2);
	ret[0] = a;
	ret[1] = b;
	return ret;
}

template <typename T>
inline std::vector<T> create_vector(const T& a, const T& b, const T& c)
{
	std::vector<T> ret(3);
	ret[0] = a;
	ret[1] = b;
	ret[2] = c;
	return ret;
}

}  // namespace stl

}  // namespace util


#endif /* UTIL_STL_VECTOR_HPP_ */
