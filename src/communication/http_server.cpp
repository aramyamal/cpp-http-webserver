#include "http_server.h"
#include "file_utils.h"
#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <unistd.h>
#include <unordered_map>

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
            std::cout << "###Sent 404 error###\n";
        }

        std::cout << "\n---- Response sent ----\n\n";

        close(fd_new_socket);
    }
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

    std::string endpoint{};
    endpoint = request.substr(4, space_index - 4);

    return serve_http_response(endpoint);
}

std::string HTTPServer::get_content_type(std::string &file_extension) {
    static const std::unordered_map<std::string, std::string> mime_types{
        {"html", "text/html; charset=UTF-8"},
        {"htm", "text/html; charset=UTF-8"},
        {"css", "text/css; charset=UTF-8"},
        {"js", "application/javascript; charset=UTF-8"},
        {"json", "application/json; charset=UTF-8"},
        {"txt", "text/plain; charset=UTF-8"},
        {"png", "image/png"},
        {"jpg", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"gif", "image/gif"},
        {"svg", "image/svg+xml"},
        {"ico", "image/x-icon"},
        {"pdf", "application/pdf"} // TODO: add more
    };

    // transform to lower case
    std::ranges::transform(file_extension, file_extension.begin(),
                           [](unsigned char c) { return std::tolower(c); });

    auto mime_it = mime_types.find(file_extension);
    return mime_it != mime_types.end() ? mime_it->second
                                       : "application/octet-stream";
}

std::optional<std::string>
HTTPServer::serve_http_response(std::string_view endpoint) {
    if (endpoint == "/") {
        endpoint = "/index.html";
    }
    endpoint.remove_prefix(1);

    std::filesystem::path file_path(endpoint);
    std::string extension{};
    std::optional<std::string> file_content{};

    if (!file_path.has_extension()) {
        extension = "html";
        file_content =
            read_file_from_dir(std::string(endpoint) + "." + extension,
                               public_dir_name, public_file_index);
    } else {
        extension = file_path.extension().string();
        extension.erase(0, 1); // remove leading dot
        file_content =
            read_file_from_dir(endpoint, public_dir_name, public_file_index);
    }

    if (!file_content.has_value()) {
        return not_found_response;
    }
    return "HTTP/1.1 200 OK\r\n"
           "Content-Type: " +
           get_content_type(extension) +
           "\r\n"
           "Content-Length: " +
           std::to_string(file_content.value().length()) +
           "\r\n"
           "Cache-Control: public, max-age=86400\r\n"
           "\r\n" +
           file_content.value();
}

} // namespace web
