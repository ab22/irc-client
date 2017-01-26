#pragma once

#include <string>

#include "event.hpp"

namespace irc {
namespace parser {
    irc::Message parse_message(std::string message);
}
}
