#ifndef HTTP_SERVER
#define HTTP_SERVER

#include <cstdint>
#include <string>
#include <netinet/in.h>

namespace server {
    class tcp_server {
    private:
        std::uint16_t _port;
        std::int32_t _sock;
        sockaddr_in _saddr_in;
        int _client_sock;
        char _recv_data[1024];
        bool _running;
        std::string _response;
        
        void listen();
    public:
       tcp_server(std::uint16_t port);
       ~tcp_server();

       void start();
       void send(std::string message);
       void set_response(std::string res) { _response = res; }

       std::string get_rec_data();
       bool is_running();
    };
}
#endif