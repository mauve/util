/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <iostream/readfile.hpp>

#include <fstream>

namespace util {

bool readfile (const std::string& path,
		std::vector<char>& buf,
		std::size_t max_size /* = 0 */,
		std::ios::openmode mode /* = std::ios::binary | std::ios::in */)
{
	std::ifstream ifs(path.c_str(), mode);
	if (!ifs.is_open())
		return false;

	return readfile(ifs, buf, max_size);
}

bool readfile (std::ifstream& ifs, std::vector<char>& buf,
		std::size_t max_size /* = 0 */)
{
	ifs.seekg(0, std::ifstream::end);
	std::size_t size = static_cast<std::size_t>(ifs.tellg());
	ifs.seekg(0, std::ifstream::beg);

	if (max_size && (max_size > size))
		size = max_size;

	if (size) {
		buf.resize(size);
		if (! ifs.read(&buf[0], size))
			return false;
	}

	return true;
}

bool readfile (const std::string& path,
		std::string& buf,
		std::size_t max_size /* = 0 */)
{
	std::vector<char> char_buf;
	if (!readfile (path, char_buf, max_size))
		return false;

	buf.assign(char_buf.begin(), char_buf.end());
	return true;
}

std::string readfile (const std::string& path,
		std::size_t max_size /* = 0 */)
{
	std::string contents;
	if (!readfile (path, contents, max_size)) {
		contents.clear();
		return contents;
	}

	return contents;
}

}  // namespace util
