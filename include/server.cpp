#include "server.hpp"
#include <iostream>
#include <sys/socket.h>
#include <stdexcept>
#include <unistd.h>
#include <cstring>
#include <fstream>

void server::tcp_server::send(std::string message) {
    write(_client_sock, message.c_str(), message.size());
    close(_client_sock);
}

void server::tcp_server::start() {
    if ((_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Error: " << errno << std::endl;
        throw std::runtime_error("Error creating socket");
    }

    _saddr_in.sin_family = AF_INET;
    _saddr_in.sin_port = htons(_port);
    _saddr_in.sin_addr.s_addr = INADDR_ANY;

    if (bind(_sock, (struct sockaddr*) &_saddr_in, sizeof(_saddr_in)) != 0) {
        std::cerr << "Error: " << errno << std::endl;
        throw std::runtime_error("Error binding socket");
    }

    if (::listen(_sock, 5) != 0) {
        std::cerr << "Error: " << errno << std::endl;
        throw std::runtime_error("Error starting to listen");
    }

    _running = true;
    std::cout << "Server is listening on port " << _port << "...\n";

    while (_running) {
        _client_sock = accept(_sock, nullptr, nullptr);
        if (_client_sock < 0) {
            std::cerr << "Error: " << errno << std::endl;
            continue; 
        }

        std::memset(_recv_data, 0, sizeof(_recv_data));
        ssize_t bytes_received = recv(_client_sock, _recv_data, sizeof(_recv_data), 0);
        if (bytes_received > 0) {
            std::cout << "Received request:\n" << _recv_data << std::endl;
        }

        send(_response);
    }
}
server::tcp_server::tcp_server(std::uint16_t port) : _port(port) {
    std::memset(_recv_data, 0, sizeof(_recv_data));
};

server::tcp_server::~tcp_server() {
    close(_sock);
    close(_client_sock);
};

void server::tcp_server::set_response(std::string res) { _response = res; }

std::string server::tcp_server::get_rec_data() { return _recv_data; }

bool server::tcp_server::is_running() { return _running; }