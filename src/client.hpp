#ifndef __IRC_CLIENT_HPP__
#define __IRC_CLIENT_HPP__

#include <array>
#include <boost/asio.hpp>

namespace irc {

class Client {
private:
    const char* _server;
    const char* _port;
    constexpr static size_t _max_msg_length = 512;
    std::array<char, _max_msg_length> _buffer;
    size_t _bytes_read;

    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::socket _socket;

    inline bool buffer_has_data() const;
    inline void shift_buffer_bytes(const std::size_t, const std::size_t);
    bool get_line_from_buffer(std::string&);

public:
    Client(const char* server, const char* port);
    void connect(boost::system::error_code&);
    std::string read_line(boost::system::error_code&);
};
}

#endif
