#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <csignal>
#include <cstring>
#include <sys/wait.h>

#include <iostream>
#include <string>

#include "Detail.h"

namespace http {

    class Server {
    public:
        Server(const std::string &ipAddress, const int &port);
        ~Server();
        void start();

    private:
        std::string ipAddress_;
        int port_;
        int fileDescriptorSocket_;
        int fileDescriptorNewSocket_;
        int connectionsCount_ = 20;
        static const int bufferSize = 1024;

    };
} // namespace http

#endif //HTTPSERVER_SERVER_H
