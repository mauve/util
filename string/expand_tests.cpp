/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <boost/test/unit_test.hpp>

#include <string/expand.hpp>

std::string replacer(const std::string& str)
{
	if (str == "a")
		return "apa";
	if (str == "b")
		return "bap";
	return "";
}

BOOST_AUTO_TEST_SUITE(util)

BOOST_AUTO_TEST_SUITE(string)

BOOST_AUTO_TEST_SUITE(expand_tests)

BOOST_AUTO_TEST_CASE(map_empty_replacements)
{
	std::map<std::string, std::string> replacements;

	std::string s1 = "no variables";
	BOOST_CHECK_EQUAL(s1, expand_copy(s1, replacements));

	std::string s2 = "variable ${a} does not exist";
	BOOST_CHECK_EQUAL("variable  does not exist", expand_copy(s2, replacements));
}

BOOST_AUTO_TEST_CASE(map_replace_some)
{
	std::map<std::string, std::string> replacements;
	replacements["a"] = "apa";
	replacements["b"] = "bap";

	std::string s = "${a} ${b}";
	BOOST_CHECK_EQUAL("apa bap", expand_copy(s, replacements));
}

BOOST_AUTO_TEST_CASE(func_replace_some)
{
	std::string s = "${a} ${b}";
	BOOST_CHECK_EQUAL("apa bap", expand_copy(s, replacer));
}

BOOST_AUTO_TEST_SUITE_END() // expand_tests

BOOST_AUTO_TEST_SUITE_END() // string

BOOST_AUTO_TEST_SUITE_END() // util
