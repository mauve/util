/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef __UTIL_STL_LIST_HPP__
#define __UTIL_STL_LIST_HPP__

#include <list>

namespace util {

namespace stl {

template <typename T>
inline std::list<T> create_list(const T& a)
{
	std::list<T> list;
	list.push_back(a);
	return list;
}

template <typename T>
inline std::list<T> create_list(const T& a, const T& b)
{
	std::list<T> list;
	list.push_back(a);
	list.push_back(b);
	return list;
}

template <typename T>
inline std::list<T> create_list(const T& a, const T& b, const T& c)
{
	std::list<T> list;
	list.push_back(a);
	list.push_back(b);
	list.push_back(c);
	return list;
}

}  // namespace stl

}  // namespace util


#endif /* __UTIL_STL_LIST_HPP__ */
