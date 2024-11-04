#include "socket.h"

namespace web {

Socket::Socket(int domain, int type, int protocol, int port,
               uint32_t interface) {
    // Define address structure
    address.sin_family = domain;
    address.sin_port = htons(port); // From host byter order network byte order
    address.sin_addr.s_addr = htonl(interface); // Byte order conversion

    // Establish socket
    fd_socket = socket(domain, type, protocol);
    test_connection(fd_socket, "Failed to establish socket.");
}

} // namespace web
