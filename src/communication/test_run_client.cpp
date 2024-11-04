#include "client.h"
#include <arpa/inet.h>

int main() {
    int interface{};
    // Convert localhost address to binary
    int address_convert_result = inet_pton(AF_INET, "127.0.0.1", &interface);
    interface = ntohl(interface);

    if (address_convert_result < 0) {
        std::cout << "Invalid adress..." << std::endl;
    }
    try {
        web::Client client_instance =
            web::Client(AF_INET, SOCK_STREAM, 0, 8080, interface);
        client_instance.run("Hello from client!");

    } catch (const std::runtime_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
