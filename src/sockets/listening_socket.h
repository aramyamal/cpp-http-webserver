#ifndef WEB_LISTENING_SOCKET_H
#define WEB_LISTENING_SOCKET_H

#include "socket.h"

namespace web {

class ListeningSocket : public Socket {
  public:
    ListeningSocket(int domain, int type, int protocol, int port,
                    uint32_t interface, int backlog);

    ~ListeningSocket() override = default;

    int accept_new_connection();

  protected:
    void establish() override;

  private:
    int m_backlog{};
    int address_length{sizeof(address)};
};

} // namespace web

#endif // WEB_LISTENING_SOCKET_H
