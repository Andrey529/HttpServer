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
        using Handler = std::function<void(const Request &, Response &)>;

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
        static const int bufferSize_ = 1024;
        Handlers handlers_;

        Server &insertHandler(const RequestType& requestType, const std::string &path, Handler &handler);
        Server &insertHandler(const RequestType& requestType, const std::string &path, Handler &&handler);

        void readRequest(std::string &requestString);
        void parseRequest(std::string &requestString, Request &request);
        void processRequestAndCreateResponse(const Request &request, Response &response);
        void sendResponse(const Response &response);
    };
} // namespace http

#endif //HTTPSERVER_SERVER_H
