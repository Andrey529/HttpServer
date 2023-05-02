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
#include <vector>
#include <unordered_map>
#include <functional>

#include "NetDetail.h"
#include "Request.h"
#include "Response.h"

namespace http {

    class Server {
    public:
        using Handler = std::function<void(const Request &, const Response &)>;

        using Handlers = std::unordered_map<RequestType, std::vector<std::pair<std::string, Handler>>>;


        Server(const std::string &ipAddress, const int &port);
        ~Server();
        void start();

        Server &Get(const std::string &path, Handler &handler);
        Server &Get(const std::string &path, Handler &&handler);
        Server &Post(const std::string &path, Handler &handler);
        Server &Post(const std::string &path, Handler &&handler);
        Server &Put(const std::string &path, Handler &handler);
        Server &Put(const std::string &path, Handler &&handler);
        Server &Delete(const std::string &path, Handler &handler);
        Server &Delete(const std::string &path, Handler &&handler);
        Server &Options(const std::string &path, Handler &handler);
        Server &Options(const std::string &path, Handler &&handler);
        Server &Head(const std::string &path, Handler &handler);
        Server &Head(const std::string &path, Handler &&handler);

    private:
        std::string ipAddress_;
        int port_;
        int fileDescriptorSocket_;
        int fileDescriptorNewSocket_;
        int connectionsCount_ = 20;
        static const int bufferSize = 1024;
        Handlers handlers;

        Server &insertHandler(const RequestType& requestType, const std::string &path, Handler &handler);
        Server &insertHandler(const RequestType& requestType, const std::string &path, Handler &&handler);

        void parseRequest();
        void processRequest();
        void sendResponse();
    };
} // namespace http

#endif //HTTPSERVER_SERVER_H
