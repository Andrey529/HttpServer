//#include "Server.h"
//
//int main(int argc, char **argv) {
//    if (argc != 3) {
//        std::cerr << "Incorrect number of input arguments. Must be\n"
//                     "<program-name> <ip-address> <port>" << std::endl;
//        return 1;
//    }
//
//    http::Server server(argv[1], std::stoi(argv[2]));
//    server.start();
//
//    return 0;
//}

#include <iostream>
#include "Request.h"

int main() {
    Request request("GET", "/", "HTTP/1.1", {}, "name=Joe%20User&request=Send%20me%20one%20of%20your%20catalogue");
    request.setHeader("Host", "developer.mozilla.org");
    request.setHeader("Content-Length", "64");
    request.setHeader("Content-Type", "application/x-www-form-urlencoded");
    request.method_ = "POST";

    std::cout << request.method_ << ' ' << request.path_ << ' ' << request.version_ << '\n';
    for (const auto & header : request.headers_) {
        std::cout << header.first << ": " << header.second << '\n';
    }

    std::cout << '\n' << request.body_ << std::endl;
}