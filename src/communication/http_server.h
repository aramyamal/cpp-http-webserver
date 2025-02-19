#ifndef WEB_HTTP_SERVER_H
#define WEB_HTTP_SERVER_H

#include "server.h"
#include "file_utils.h"
#include <optional>

namespace web {

class HTTPServer : public Server {
  public:
    HTTPServer(int port = 80, int backlog = 10)
        : Server(AF_INET, SOCK_STREAM, 0, port, INADDR_ANY, backlog) {}

    virtual ~HTTPServer() = default;

    void run(); // parent class has run(std::string response), potentially fix

  private:
    std::optional<std::string> process_request(std::string_view request);
    std::optional<std::string> serve_http_response(std::string_view endpoint);
    std::string get_content_type(std::string &file_extension);
    std::string not_found_html = read_file("error_404.html").value();
    std::string not_found_response =
        "HTTP/1.1 404 Not Found\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n"
        "Content-Length: " +
        std::to_string(not_found_html.length()) +
        "\r\n"
        "\r\n" +
        not_found_html;
};

} // namespace web

#endif // WEB_HTTP_SERVER_H
