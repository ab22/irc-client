#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

namespace irc {
namespace event {
    struct MessagePrefix {
        // Stores nick of who sent the message, server name or empty string.
        std::string name;
        // Stores user who sent the message or empty string.
        std::string user;
        // Stores the host of who sent the message or a blank string.
        std::string host;

        void print()
        {
            std::cout << "Prefix Name: " << name << "\n";
            std::cout << "Prefix User: " << user << "\n";
            std::cout << "Prefix Host: " << host << "\n";
        }
    };

    struct Message {
        MessagePrefix prefix;
        std::string command;
        std::vector<std::string> params;

        void print()
        {
            prefix.print();
            std::cout << "Command: " << command << "\n";

            for (auto p : params) {
                std::cout << "Param: " << p << "\n";
            }
        }
    };
}
}
