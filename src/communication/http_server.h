#pragma once

#include "file_utils.h"
#include "server.h"
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
    std::vector<std::string> public_file_index = index_public();
    const std::string public_dir_name = "public";
    const std::string not_found_html =
        read_file_from_dir("error_404.html", public_dir_name, public_file_index)
            .value_or(R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>404 Not Found</title>
</head>
<body>
    <h1>404 Not Found</h1>
    <p>The requested resource could not be found.</p>
</body>
</html>
)");

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
