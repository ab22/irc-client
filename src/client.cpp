#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>

#include "client.hpp"
#include "event.hpp"
#include "utils.hpp"

using namespace boost;
using boost::asio::ip::tcp;

irc::Client::Client(const char* server, const char* port)
    : _server(server)
    , _port(port)
    , _bytes_read(0)
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

inline bool irc::Client::buffer_has_data() const
{
    return _bytes_read > 0;
}

inline void irc::Client::shift_buffer_bytes(const std::size_t start, const std::size_t end)
{
    for (size_t src = start, dst = 0; src < end; src++, dst++) {
        _buffer[dst] = _buffer[src];
    }
}

bool irc::Client::get_line_from_buffer(std::string& line)
{
    if (!buffer_has_data())
        return false;

    std::string buffer(_buffer.data(), _bytes_read);
    std::size_t pos = buffer.find("\r\n");

    if (pos == std::string::npos)
        return false;

    // Include "\r\n"
    pos += 2;
    line = buffer.substr(0, pos);
    shift_buffer_bytes(pos, _bytes_read);
    _bytes_read -= pos;

    return true;
}

std::string irc::Client::read_line(system::error_code& err)
{
    std::string line;

    if (get_line_from_buffer(line)) {
        return line;
    }

    size_t bytes_to_read;

    while (true) {
        bytes_to_read = _max_msg_length - _bytes_read;
        auto buffer = asio::buffer(_buffer.data() + _bytes_read, bytes_to_read);

        _bytes_read += _socket.read_some(buffer, err);

        if (err)
            return line;

        if (get_line_from_buffer(line))
            return line;

        if (_bytes_read >= _max_msg_length)
            throw "read until: max msg length read and no crlf found!";
    }
}
