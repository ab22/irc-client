#include "parser.hpp"

#include <iostream>
#include "event.hpp"
#include "utils.hpp"

irc::Message irc::parser::parse_message(std::string& msg)
{
    std::size_t pos = msg.find("\r\n");

    if (pos == std::string::npos)
        throw "parse message: no crlf found!";

    msg = msg.substr(0, msg.length() - 2);

    if (msg.length() == 0)
        throw "parse message: empty message!";

    irc::Message message;

    if (msg[0] == ':') {
        pos = msg.find(" ");

        if (pos == std::string::npos)
            throw "parse message: no data after prefix";

        message.prefix.name = msg.substr(1, pos - 1);

        if (pos + 1 >= msg.length())
            throw "parse message: no command found";

        msg = msg.substr(pos + 1);
    }

    pos = msg.find(" :");

    if (pos == std::string::npos) {
        message.command = msg;
        return message;
    }

    auto cmd = msg.substr(0, pos);
    auto params = strutils::split(cmd, " ");

    if (params.size() == 0)
        throw "parse message: no command found";

    message.command = params[0];
    msg = msg.substr(pos + 2);
    message.params = strutils::split(msg, " ");

    if (params.size() > 0) {
        message.params.insert(message.params.begin(), params.begin(), params.end());
    }

    return message;
}
