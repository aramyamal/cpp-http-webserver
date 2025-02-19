#include "http_server.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string usage_description{"Usage: " + std::string(argv[0]) +
                                  " <port> <backlog>"};

    if (argc != 3) {
        std::cerr << usage_description << std::endl;
        return 1;
    }

    try {
        int port = std::stoi(argv[1]);
        int backlog = std::stoi(argv[2]);

        web::HTTPServer server = web::HTTPServer(port, backlog);
        server.run();
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
