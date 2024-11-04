#include "listening_socket.h"

namespace web {

ListeningSocket::ListeningSocket(int domain, int type, int protocol, int port,
                                 uint32_t interface, int backlog)
    : Socket(domain, type, protocol, port, interface), m_backlog{backlog} {
    establish();
};

int ListeningSocket::accept_new_connection() {
    int fd_new_socket =
        accept(fd_socket, reinterpret_cast<struct sockaddr *>(&address),
               reinterpret_cast<socklen_t *>(&address_length));
    test_connection(fd_new_socket, "Failed to accept connection.");
    return fd_new_socket;
}

void ListeningSocket::establish() {
    int bind_status =
        bind(fd_socket, reinterpret_cast<struct sockaddr *>(&address),
             address_length);
    test_connection(bind_status, "Failed to bind socket.");
    int listen_status = listen(fd_socket, m_backlog);
    test_connection(listen_status, "Failed to start listening on socket.");
}

} // namespace web
