#include <iostream>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>
#include "client.hpp"

const char* SERVER = "localhost";
const char* PORT = "6667";

int main()
{
    irc::Client c(SERVER, PORT);
    boost::system::error_code err;

    std::cout << "Conecting to server [" << SERVER << ":" << PORT << "]...\n";
    c.connect(err);

    if (err) {
        std::cout << "Error ocurred: " << err.message() << "\n";
        return -1;
    }

    std::cout << "Listening...\n";
    c.listen(err);

    if (err != boost::asio::error::eof) {
        std::cout << "Error ocurred: " << err.message() << "\n";
        return -1;
    }

    return 0;
}
