#ifndef __IRC_PARSER_HPP__
#define __IRC_PARSER_HPP__

#include <string>

#include "event.hpp"

namespace irc {
namespace parser {
    irc::Message parse_message(std::string& message);
}
}

#endif
