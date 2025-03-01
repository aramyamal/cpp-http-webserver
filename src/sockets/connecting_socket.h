#pragma once

#include "socket.h"
#include <unistd.h>

namespace web {

class ConnectingSocket : public Socket {
  public:
    ConnectingSocket(int domain, int type, int protocol, int port,
                     uint32_t interface);

    ~ConnectingSocket() override = default;

    void send_message(std::string message) {
        send(fd_socket, message.c_str(), message.length(), 0);
    }

    int read_message(char* buffer, size_t size) {
        return read(fd_socket, buffer, size);
    }

  protected:
    void establish() override;
};

} // namespace web
