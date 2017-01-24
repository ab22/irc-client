#ifndef __IRC_UTILS_HPP__
#define __IRC_UTILS_HPP__

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

namespace strutils {
std::vector<std::string> split(const std::string& s, const std::string& delim, const bool keep_empty = true);
}

#endif
