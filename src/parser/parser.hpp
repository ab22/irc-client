#pragma once

#include <string>

#include "../event/event.hpp"

namespace irc {
namespace parser {
    irc::event::Message parse_message(std::string message);
}
}
