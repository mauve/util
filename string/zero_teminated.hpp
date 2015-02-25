/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#ifndef UTIL_PROCESS__DETAIL_ZERO_TEMINATED_HPP_
#define UTIL_PROCESS__DETAIL_ZERO_TEMINATED_HPP_

#include <vector>
#include <string>

namespace util {

class zero_terminated_list_of_strings
{
public:
	void add (const std::string& s);
	void add (const std::vector<std::string>& s);

	char** data();

private:
  std::vector<char*> _buf;
  std::vector<std::string> _strings;
};

}  // namespace util

#endif /* UTIL_PROCESS__DETAIL_ZERO_TEMINATED_HPP_ */
