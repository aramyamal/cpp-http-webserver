#include "server.h"
#include <cstring>
#include <array>

namespace web {

Server::Server(int domain, int type, int protocol, int port, uint32_t interface,
               int backlog)
    : listening_socket(domain, type, protocol, port, interface, backlog) {}

void Server::run(std::string response) {

    // TODO: Implement dynamic chunk reading for large requests
    while (true) {
        std::cout << "\n---- Waiting for new connection ----\n\n";
        fd_new_socket = listening_socket.accept_new_connection();

        std::array<char, 8192> buffer{};
        read(fd_new_socket, buffer.data(), buffer.size());

        std::string request = buffer.data();
        std::cout << "Recieved request:\n" << request << "\n";

        write(fd_new_socket, response.c_str(), response.length());
        std::cout << "\n---- Response sent ----\n\n";

        close(fd_new_socket);
    }
}

} // namespace web
