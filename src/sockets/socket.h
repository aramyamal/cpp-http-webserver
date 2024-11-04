#ifndef WEB_SOCKET_H
#define WEB_SOCKET_H

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace web {

/// Abstract base class for a socket.
class Socket {
  public:
    /// Initializes socket.
    ///
    /// @param domain           Communication domain, AF_INET (value: 2) for
    ///                         IPv4.
    /// @param type             Type of service. Usually SOCK_STREAM (value: 1)
    ///                         for TCP.
    /// @param protocol         Specific protocol, 0 for TCP.
    /// @param port             Port number (0-65535).
    /// @param interface        The address to bind to.
    Socket(int domain, int type, int protocol, int port, uint32_t interface);

    virtual ~Socket() = default;

  protected:
    /// Virtual method implemented in derived socket classes.
    virtual void establish() = 0;

    /// Tests connection status for a connecting action. 
    void test_connection(int result, std::string_view error_message) const {
        if (result < 0) {
            throw std::runtime_error(std::string(error_message));
        }
    }

    struct sockaddr_in address{};
    int fd_socket{};     // Low level file descriptor
};

} // namespace web

#endif // WEB_SOCKET_H
