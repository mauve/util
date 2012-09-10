/*
 * Copyright (C) 2012, All rights reserved, Mikael Olenfalk <mikael@olenfalk.se>
 */

#include <stupidtest/stupidtest.hpp>

#include <cstdlib>
#include <iostream>

namespace util {

namespace stupidtest {

namespace {

const char* g_suite_name = 0;
bool g_verbose = false;
bool g_under_teamcity = false;
std::ostream* g_output = 0;

std::ostream& output()
{
	if (g_output)
		return *g_output;
	return std::cerr;
}

void report_suite_ended ()
{
	if (g_under_teamcity) {
		output() << "##teamcity[testSuiteEnded name='" << g_suite_name << "']" << std::endl;
	} else {
		output() << "...test suite ended." << std::endl;
	}
}

}  // namespace


void setup (const char* suite_name, bool verbose, std::ostream& target /* = std::cerr */, bool no_at_exit_handler /* = false */)
{
	output() << std::flush;

	g_suite_name = suite_name;
	g_verbose = verbose;
	g_under_teamcity = !!std::getenv("TEAMCITY_PROJECT_NAME");
	g_output = &target;

	if (!no_at_exit_handler)
		std::atexit(&report_suite_ended);

	if (g_under_teamcity) {
		output() << "##teamcity[testSuiteStarted name='" << g_suite_name << "']" << std::endl;
	} else {
		output() << "Starting Test Suite: " << g_suite_name << std::endl;
	}
}

namespace _detail {

void report_case_start(const char* name)
{
	if (g_under_teamcity) {
		output() << "##teamcity[testStarted name='" << name << "' captureStandardOutput='true']" << std::endl;
	} else {
		output() << "  Running test case " << name << ": " << std::endl;
	}
}

void report_case_ended(const char* name, bool succeeded, const char* message)
{
	if (g_under_teamcity) {
		if (!succeeded)
			output() << "##teamcity[testFailed name='" << name << "' message='" << message << "']" << std::endl;
		output() << "##teamcity[testEnded name='" << name << "']" << std::endl;
	} else {
		if (!succeeded)
			output() << "  ..failed (message: " << message << ")" << std::endl;
		else
			output() << "  ..succeeded" << std::endl;
	}
}

void report_check_before(const char* name)
{
	if (g_under_teamcity)
		return;

	output() << "     Running check: " << name << ": " << std::flush;
}

void report_check_after(const char* name, bool succeeded, const char* message /* = 0 */)
{
	if (g_under_teamcity) {
		if (succeeded)
			return;

		output() << "##teamcity[testFailed name='" << name << "' message='" << message << "']" << std::endl;
	} else {
		if (!succeeded)
			output() << "failed (message: " << message << ")" << std::endl;
		else
			output() << "succeeded" << std::endl;
	}
}

}  // namespace _detail

}  // namespace stupidtest

}  // namespace util
