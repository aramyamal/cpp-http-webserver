#include "connecting_socket.h"

namespace web {
ConnectingSocket::ConnectingSocket(int domain, int type, int protocol, int port,
                                   uint32_t interface)
    : Socket(domain, type, protocol, port, interface) {
    establish();
};

void ConnectingSocket::establish() {
    int connect_status =
        connect(fd_socket, reinterpret_cast<struct sockaddr *>(&address),
                sizeof(address));
    test_connection(connect_status, "Failed to connect socket.");
}

} // namespace web
