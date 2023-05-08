#include "Server.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Incorrect number of input arguments. Must be\n"
                     "<program-name> <ip-address> <port>" << std::endl;
        return 1;
    }

    http::Server server(argv[1], std::stoi(argv[2]));

    server.Get("/sample", [](const http::Request &, http::Response &response){
        response.set_content("<html><body><h1>sample</h1></body></html>", "text/html");
    });

    server.Get("/empty", [](const http::Request &, http::Response &response){

    });

    server.Get("/text", [](const http::Request &, http::Response &response){
        response.set_content("Text plain", "text/plain");
    });

    server.Post("/post", [](const http::Request &, http::Response &response){
        response.set_content("Post", "text/plain");
    });


    server.start();

    return 0;
}