
#ifndef __UTIL_MEMORY__READ_HPP__
#define __UTIL_MEMORY__READ_HPP__

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_pod.hpp>

#include <cstring>

namespace util {

namespace memory {

template <typename T>
typename boost::enable_if< boost::is_pod<T>, T>::type
read_unaligned (const char* memory, std::size_t offset = 0)
{
	T result;
	std::memcpy(&result, memory + offset, sizeof(T));
	return result;
}

template <typename T>
typename boost::enable_if< boost::is_pod<T>, T>::type
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
