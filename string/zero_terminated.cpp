/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include "zero_teminated.hpp"

#include <cstring>

namespace util {

void zero_terminated_list_of_strings::add (const std::string& s)
{
  _strings.push_back(s);
}

void zero_terminated_list_of_strings::add (const std::vector<std::string>& strings)
{
	for (auto&& s : strings)
		add(s);
}

char** zero_terminated_list_of_strings::data()
{
  _buf.clear();
  _buf.shrink_to_fit();

  for (auto&& s : _strings)
    _buf.push_back(&s[0]);
  _buf.push_back(nullptr);

	return &*(_buf.begin());
}

}  // namespace util

