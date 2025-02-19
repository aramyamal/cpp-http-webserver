#ifndef WEB_CLIENT_H
#define WEB_CLIENT_H

#include "connecting_socket.h"

namespace web {

class Client {

  public:
    Client(int domain, int type, int protocol, int port, uint32_t interface);

    virtual ~Client() = default;

    void run(std::string request);

  private:
    ConnectingSocket connecting_socket;
};

} // namespace web

#endif // WEB_CLIENT_H
