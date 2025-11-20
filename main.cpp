#include <iostream>
#include <cstdint>
#include <limits>
#include <fstream>
#include "include/server.hpp"

std::uint16_t stous(const char* s) {
    int i = std::stoi(s);
    if (i > std::numeric_limits<std::uint16_t>::max() && i < std::numeric_limits<std::uint16_t>::min()) {
        throw std::out_of_range("number out of range");
    }
    return i;
}

int main(int argc, const char** argv) {
    std::uint16_t port = stous(argv[1]);
    server::tcp_server server(port);

    server.set_response("test response");
    server.start();
    std::cout << server.get_rec_data();
    
    return 0;
}