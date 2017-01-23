#ifndef __IRC_CLIENT_HPP__
#define __IRC_CLIENT_HPP__

#include <boost/asio.hpp>

namespace irc {

class Client {
private:
    const char* _server;
    const char* _port;

    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::socket _socket;

public:
    Client(const char* server, const char* port);
    void connect(boost::system::error_code&);
    void listen(boost::system::error_code&);
};
}

#endif
