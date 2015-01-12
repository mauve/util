
#ifndef __PLATFORM__ENVIRONMENT_HPP__
#define __PLATFORM__ENVIRONMENT_HPP__

#include <map>
#include <string>

namespace platform
{

// initialized during startup, doesnt change after that
// none of the other functions use this variable
extern const std::map<std::string, std::string> environment;

// reflects recent changes
std::map<std::string, std::string> get_environment();

// reflects recent changes
std::string get_environment_variable(const std::string& variable, const std::string& default_value);

// reflects recent changes
bool has_environment_variable(const std::string& variable);

}  // namespace platform

#endif  // __PLATFORM__ENVIRONMENT_HPP__