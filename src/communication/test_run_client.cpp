#include "client.h"
#include <arpa/inet.h>
#include <iostream>
#include <string>

//Simple client side tcp to test if server is working without browser
int main(int argc, char *argv[]) {
     std::string usage_description{"Usage: " + std::string(argv[0]) +
         " <address> <port> <message>"};

    if (argc != 4) {
        std::cerr << usage_description << std::endl;
        return 1;
    }

    int interface{};
    // Convert address to binary
    int address_convert_result = inet_pton(AF_INET, argv[1], &interface);
    interface = ntohl(interface);

    if (address_convert_result < 0) {
        std::cout << "Invalid adress..." << std::endl;
    }
    try {
        web::Client client_instance =
            web::Client(AF_INET, SOCK_STREAM, 0, std::stoi(argv[2]), interface);
        client_instance.run(argv[3]);

    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}

