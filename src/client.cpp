#include <iostream>
#include <array>
#include <algorithm>
#include <iterator>

#include "event.hpp"
#include "client.hpp"
#include "utils.hpp"
#include "parser.hpp"

using namespace boost;
using boost::asio::ip::tcp;

irc::Client::Client(const char* server, const char* port)
    : _server(server)
    , _port(port)
    , _socket(_io_service)
{
}

void irc::Client::connect(system::error_code& err)
{
    tcp::resolver resolver(_io_service);
    tcp::resolver::query query(_server, _port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query, err);

    if (err)
        return;

    asio::connect(_socket, endpoint_iterator, err);
}

void irc::Client::read_message(system::error_code& err)
{
    std::array<char, 512> buf;
    size_t bytes_read = 0;

    while (true) {
        bytes_read = _socket.read_some(boost::asio::buffer(buf), err);

        if (err)
            return;

        std::cout << ">> ";
        std::cout.write(buf.data(), bytes_read);

        std::string msg(buf.data());
        auto message = irc::parser::parse_message(msg);
        message.print();
    }
}
