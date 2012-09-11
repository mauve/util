/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <string/expand.hpp>
#include <boost/regex.hpp>
#include <boost/ref.hpp>

#include <iostream>

namespace util {

typedef std::map<std::string, std::string> map_t;

namespace {

struct map_replacer :
	public std::unary_function<const boost::smatch&, const std::string&>
{
public:
	map_replacer (const map_t& replacements)
		: _replacements(replacements)
	{}

	const std::string& operator() (const boost::smatch& match) const
	{
		map_t::const_iterator iter = _replacements.find(match[1]);
		if (iter == _replacements.end())
			return _empty;

		return iter->second;
	}

private:
	const map_t& _replacements;
	std::string _empty;
};

struct func_replacer :
	public std::unary_function<const boost::smatch&, std::string>
{
	func_replacer (const boost::function<std::string(const std::string&)>& replacer)
		: _replacer(replacer)
	{}

	std::string operator() (const boost::smatch& match) const
	{
		if (!_replacer)
			return "";

		return _replacer(match[1]);
	}

private:
	const boost::function<std::string(const std::string&)>& _replacer;
};

}  // namespace

std::string expand_copy (const std::string& haystack, const map_t& replacements)
{
	boost::regex rx("\\$\\{([^}]+)\\}");
	map_replacer replacer_func(replacements);
	return boost::regex_replace(haystack, rx, replacer_func);
}

std::string expand_copy (const std::string& haystack, const boost::function<std::string(const std::string&)>& replacer)
{
	boost::regex rx("\\$\\{([^}]+)\\}");
	func_replacer replacer_func(replacer);
	return boost::regex_replace(haystack, rx, replacer_func);
}

}  // namespace util
