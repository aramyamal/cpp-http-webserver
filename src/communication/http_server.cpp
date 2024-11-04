#include "http_server.h"
#include <array>
#include <fstream>

namespace web {

void HTTPServer::run() {

    std::array<char, 8192> buffer{};
    // TODO: Implement dynamic chunk reading for large requests
    while (true) {
        std::cout << "\n---- Waiting for new connection ----\n\n";
        fd_new_socket = listening_socket.accept_new_connection();

        // Reset the buffer using std::fill
        std::fill(buffer.begin(), buffer.end(), '\0');

        read(fd_new_socket, buffer.data(), buffer.size());

        std::string request = buffer.data();
        std::cout << "###Recieved request:###\n\n" << request << "\n";

        std::cout << "###Responding with:###\n\n";
        auto response = process_request(request);
        if (response.has_value()) {
            write(fd_new_socket, response.value().c_str(),
                  response.value().length());
            std::cout << response.value().substr(0, 500) << "\n.\n.\n.\n";
        } else {
            write(fd_new_socket, not_found_response.c_str(),
                  not_found_response.length());
            std::cout << response.value().substr(0, 500) << "\n.\n.\n.\n";
        }

        std::cout << "\n---- Response sent ----\n\n";

        close(fd_new_socket);
    }
}

std::string HTTPServer::read_file(std::string_view path) {
    std::ifstream file(path.data(), std::ios::ate); // ate moves pointer to end

    if (!file.is_open()) {
        return ""; // fix this to throw exception
    }

    // Get filesize
    auto file_size = file.tellg(); // read file size with position of pointer
    std::string content(file_size, '\0'); // allocate needed space

    file.seekg(0); // move pointer to beginning

    file.read(content.data(), file_size); // write to cstring used by
                                          // std::string
    return content;
}

std::optional<std::string>
HTTPServer::process_request(std::string_view request) {
    if (request.substr(0, 4) != "GET ") {
        return std::nullopt; // 'GET' not in the beginning of the request
    }

    // Find the index of the first space after "GET "
    size_t space_index = request.find(' ', 4);
    if (space_index == std::string::npos) {
        return std::nullopt; // No space found after 'GET'
    }

    std::string path{};
    path = request.substr(4, space_index - 4);

    // TODO: method that serves http headers to reduce code repetition and
    // future scalabity
    if (path == "/index.html" || path == "/") {
        std::string response = read_file("index.html");
        return "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html; charset=UTF-8\r\n"
               "Content-Length: " +
               std::to_string(response.length()) +
               "\r\n"
               "Connection: keep-alive\r\n"
               "Server: cpp-webserver\r\n"
               "\r\n" +
               response;

    } else if (path == "/style.css") {
        std::string response = read_file("style.css");
        return "HTTP/1.1 200 OK\r\n"
               "Content-Type: text/css; charset=UTF-8\r\n"
               "Content-Length: " +
               std::to_string(response.length()) +
               "\r\n"
               "Connection: keep-alive\r\n"
               "Server: cpp-webserver\r\n"
               "\r\n" +
               response;

    } else if (path == "/favicon.ico") {
        std::string response = read_file("favicon.ico");
        return "HTTP/1.1 200 OK\r\n"
               "Content-Type: image/x-icon\r\n"
               "Content-Length: " +
               std::to_string(response.length()) +
               "\r\n"
               "Cache-Control: public, max-age=86400\r\n"
               "\r\n" +
               response;
    } else {
        return std::nullopt;
    }
}

} // namespace web
