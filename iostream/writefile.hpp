/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_IOSTREAM_WRITEFILE_HPP_
#define UTIL_IOSTREAM_WRITEFILE_HPP_

#include <ios>
#include <vector>
#include <string>

namespace util {

bool writefile (const std::string& path, const std::string& buf,
		std::ios::openmode mode = std::ios::binary | std::ios::out | std::ios::trunc);

bool writefile (const std::string& path, const std::vector<char>& buf,
		std::ios::openmode mode = std::ios::binary | std::ios::out | std::ios::trunc);

bool writefile (const std::string& path, const char* const buf,
		std::size_t buf_size,
		std::ios::openmode mode = std::ios::binary | std::ios::out | std::ios::trunc);

}  // namespace util

#endif /* UTIL_IOSTREAM_WRITEFILE_HPP_ */
