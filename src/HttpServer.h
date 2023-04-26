#ifndef HTTPSERVER_HTTPSERVER_H
#define HTTPSERVER_HTTPSERVER_H

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <cstring>

#include <iostream>
#include <string>

namespace http {

    enum class HttpRequestType {
        GET,
        POST,
        UPDATE,
        DELETE,
        OPTIONS
    };

    class HttpServer {
    public:
        HttpServer(const std::string &ipAddress, const int &port);
        ~HttpServer() = default;
        void startServer();

    private:
        std::string ipAddress_;
        int port_;
        int fileDescriptorSocket_;
        int fileDescriptorNewSocket_;

        void *get_in_addr(struct sockaddr *sa);

    };
}

#endif //HTTPSERVER_HTTPSERVER_H
