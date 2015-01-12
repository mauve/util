
#include "environment.hpp"

#include <cstdlib>

namespace platform
{

const std::map<std::string, std::string> environment = get_environment();

std::map<std::string, std::string> get_environment()
{
  std::map<std::string, std::string> result;
  
  for (char** item = environ; *item; ++item) {
    std::string key = *item;
    std::string value = key.substr(key.find_first_of('='));
    result.insert(std::make_pair(key, value));
  }

  return result;
}

std::string get_environment_variable(const std::string& variable, const std::string& default_value)
{
#ifdef _WIN32
  char* buffer;
  if (_dupenv_s(&buffer, nullptr, variable.c_str()))
    return default_value;

  if (!buffer)
    return default_value;
    
  std::string result{ buffer };
  free(buffer);
  return result;
#else
  char* result = std::getenv(variable.c_str());
  if (!result)
    return default_value;
  return result;
#endif
}

bool has_environment_variable(const std::string& variable)
{
#ifdef _WIN32
  char* buffer;
  if (!_dupenv_s(&buffer, nullptr, variable.c_str()))
    return false;
  
  if (!buffer)
    return false;

  free(buffer);
  return true;
#else
  return !!std::getenv(variable.c_str());
#endif
}

}  // namespace platform