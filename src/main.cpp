#include "Server.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Incorrect number of input arguments. Must be\n"
                     "<program-name> <ip-address> <port>" << std::endl;
        return 1;
    }

    http::Server server(argv[1], std::stoi(argv[2]));

    server.Get("/da", [](const http::Request &, const http::Response &){
        std::cout << "da" << std::endl;
    });

    auto golova = [](const http::Request &, const http::Response &){
        std::cout << "Sho ti golova" << std::endl;
    };
    server.Get("/golova", golova);

    server.start();

    return 0;
}