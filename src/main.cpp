#include "client.hpp"
#include "parser/parser.hpp"

#include <array>
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>
#include <string>

const char* SERVER = "localhost";
const char* PORT = "6667";

int main()
{
    irc::Client c(SERVER, PORT);
    boost::system::error_code err;

    std::cout << "Conecting to server [" << SERVER << ":" << PORT << "]...\n";
    c.connect(err);

    if (err) {
        std::cout << "Could not connect to server: " << err.message() << "\n";
        return -1;
    }

    std::cout << "Listening...\n";
    try {
        while (true) {
            std::string line = c.read_line(err);

            if (err == boost::asio::error::eof) {
                std::cout << "End of stream found!\n";
                break;
            } else if (err) {
                std::cout << "Error ocurred: " << err.message() << "\n";
                return -1;
            }

            auto message = irc::parser::parse_message(line);
            std::cout << "Message: " << line << "\n";
            message.print();
        }
    } catch (const char* msg) {
        std::cout << "Error: " << msg << "\n";
    }

    std::cout << "Connection terminated!\n";

    return 0;
}
