/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <iostream/writefile.hpp>

#include <fstream>

namespace util {

bool writefile (const std::string& path,
		const char* const buf,
		std::size_t buf_size,
		std::ios::openmode mode /* = binary | out | trunc */)
{
	std::ofstream ofs(path.c_str(), mode);
	if (!ofs.is_open())
		return false;

	return !!ofs.write(buf, buf_size);
}

bool writefile (const std::string& path,
		const std::string& buf,
		std::ios::openmode mode /* = binary | out | trunc */)
{
	return writefile(path, buf.c_str(), buf.length(), mode);
}

bool writefile (const std::string& path,
		const std::vector<char>& buf,
		std::ios::openmode mode /* = binary | out | trunc */)
{
	return writefile(path, &buf[0], buf.size(), mode);
}

}  // namespace util



