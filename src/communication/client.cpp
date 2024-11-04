#include "client.h"
#include <cstring>
#include <array>

namespace web {

Client::Client(int domain, int type, int protocol, int port, uint32_t interface)
    : connecting_socket(domain, type, protocol, port, interface) {}

void Client::run(std::string request) {

    // TODO: Implement dynamic chunk reading for large message (e.g files)
    connecting_socket.send_message(request.c_str());
    std::cout << "Request sent\n";

    std::array<char, 1024> buffer{}; 
    int valread = connecting_socket.read_message(buffer.data(), 1024);

    std::string message = buffer.data();
    std::cout << "Recieved message: /n" << message << std::endl;
}

} // namespace web
