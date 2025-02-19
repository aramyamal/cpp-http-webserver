#ifndef WEB_SERVER_H
#define WEB_SERVER_H

#include "listening_socket.h"

namespace web {

class Server {

  public:
    Server(int domain, int type, int protocol, int port, uint32_t interface,
           int backlog);

    virtual ~Server() = default;

    void run(std::string response);

  protected:
    ListeningSocket listening_socket;
    int fd_new_socket{}; 
};

} // namespace web

#endif // WEB_SERVER_H
