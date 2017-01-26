#pragma once

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace strutils {
std::vector<std::string> split(const std::string& s, const std::string& delim, const bool keep_empty = true);
}
