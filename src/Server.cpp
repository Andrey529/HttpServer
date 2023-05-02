#include <sstream>
#include "Server.h"

http::Server::Server(const std::string &ipAddress, const int &port) : ipAddress_(ipAddress), port_(port),
                                                                      fileDescriptorSocket_(),
                                                                      fileDescriptorNewSocket_(),
                                                                      connectionsCount_() {
    if (port < 1024 || port > 65535) {
        std::cerr << "Invalid port number. Port must be in [1024; 65535]" << std::endl;
        exit(1);
    }

    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    status = getaddrinfo(ipAddress.c_str(), std::to_string(port_).c_str(), &hints, &servinfo);

    if (status != 0) {
        std::cerr << "getaddrinfo error: " << gai_strerror(status) << std::endl;
        exit(1);
    }

    std::cout << "Ip address = " << ipAddress_ << " , port = " << port_ << std::endl;

    for (auto p = servinfo; p != nullptr; p = p->ai_next) {

        fileDescriptorSocket_ = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if (fileDescriptorSocket_ == -1) {
            std::cerr << "Server socker error: continue. Error number = " << errno << std::endl;
            continue;
        }

        int yes = 1;
        if (setsockopt(fileDescriptorSocket_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            std::cerr << "Error: setsockopt" << std::endl;
            exit(1);
        }

        status = bind(fileDescriptorSocket_, p->ai_addr, p->ai_addrlen);
        if (status == -1) {
            std::cerr << "Server bind error: continue. Error number = " << errno << std::endl;
            continue;
        }

        break;
    }

    if (servinfo == nullptr) {
        std::cerr << "Server failed to bind" << std::endl;
        exit(1);
    }

    freeaddrinfo(servinfo);
}

void http::Server::start() {
    int status = listen(fileDescriptorSocket_, connectionsCount_);
    if (status == -1) {
        std::cerr << "Error listen" << std::endl;
        exit(1);
    }


    // clearing of all dead processes
    struct sigaction sa;
    sa.sa_handler = http::detail::net::sigchld_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, nullptr) == -1) {
        std::cerr << "Error sigaction" << std::endl;
        exit(1);
    }

    struct sockaddr_storage their_address;
    socklen_t sin_size;
    while (true) {
        sin_size = sizeof(their_address);
        fileDescriptorNewSocket_ = accept(fileDescriptorSocket_, (struct sockaddr *) &their_address, &sin_size);
        if (fileDescriptorNewSocket_ == -1) {
            std::cerr << "Accept error, continue" << std::endl;
            continue;
        }

        std::cout << "====== New connection ======\n" << std::endl;

        char remoteHost[INET6_ADDRSTRLEN];
        inet_ntop(their_address.ss_family, http::detail::net::get_in_addr((struct sockaddr *) &their_address),
                  remoteHost,
                  sizeof(remoteHost));
        std::cout << "Server get connection from: " << remoteHost << '\n' << std::endl;

        // spawning a new process
        if (!fork()) {
            close(fileDescriptorSocket_); // this socket does not need to be listened to, it is only needed for the parent process

            std::cout << "------ Received Request from client ------\n" << std::endl;
            // read request
            char buffer[bufferSize] = {0};
            ssize_t bytesReceived = read(fileDescriptorNewSocket_, buffer, bufferSize);
            if (bytesReceived < 0) {
                std::cout << "Failed to read bytes from client socket connection" << std::endl;
            } else {
                std::cout << buffer << std::endl;
            }

            // creating response
            std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
            std::ostringstream ss;
            ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
               << htmlFile;

            // send response
            ssize_t bytesSent = send(fileDescriptorNewSocket_, ss.str().c_str(), ss.str().size(), 0);

            std::cout << "------ Server Response sent to client ------\n" << std::endl;
            std::cout << ss.str() << '\n' << std::endl;


            if (bytesSent < 0) {
                std::cerr << "Failed to send bytes to client socket connection" << std::endl;
            }

            close(fileDescriptorNewSocket_);
            exit(0);
        }
        close(fileDescriptorNewSocket_); // there is no need to listen to this socket, the parent process does not need it
    }
}

http::Server::~Server() {
    close(fileDescriptorSocket_);
}

http::Server &http::Server::insertHandler(const http::RequestType &requestType, const std::string &path,
                                          http::Server::Handler &handler) {
    if (handlers.contains(requestType)) {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = handlers.at(requestType);
        handlersWithPath.emplace_back(path, handler);
        handlers.at(requestType) = handlersWithPath;
    } else {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = {};
        handlersWithPath.emplace_back(path, handler);
        handlers.emplace(requestType, handlersWithPath);
    }
    return *this;
}

http::Server &http::Server::insertHandler(const http::RequestType &requestType, const std::string &path,
                                          http::Server::Handler &&handler) {
    if (handlers.contains(requestType)) {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = handlers.at(requestType);
        handlersWithPath.emplace_back(path, std::move(handler));
        handlers.at(requestType) = handlersWithPath;
    } else {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = {};
        handlersWithPath.emplace_back(path, std::move(handler));
        handlers.emplace(requestType, handlersWithPath);
    }
    return *this;
}

http::Server &http::Server::Get(const std::string &path, http::Server::Handler &handler) {
    return insertHandler(RequestType::GET, path, handler);
}

http::Server &http::Server::Get(const std::string &path, http::Server::Handler &&handler) {
    return insertHandler(RequestType::GET, path, std::move(handler));
}

http::Server &http::Server::Post(const std::string &path, http::Server::Handler &handler) {
    return insertHandler(RequestType::POST, path, handler);
}

http::Server &http::Server::Post(const std::string &path, http::Server::Handler &&handler) {
    return insertHandler(RequestType::POST, path, std::move(handler));
}

http::Server &http::Server::Put(const std::string &path, http::Server::Handler &handler) {
    return insertHandler(RequestType::PUT, path, handler);;
}

http::Server &http::Server::Put(const std::string &path, http::Server::Handler &&handler) {
    return insertHandler(RequestType::PUT, path, std::move(handler));
}

http::Server &http::Server::Delete(const std::string &path, http::Server::Handler &handler) {
    return insertHandler(RequestType::DELETE, path, handler);
}

http::Server &http::Server::Delete(const std::string &path, http::Server::Handler &&handler) {
    return insertHandler(RequestType::DELETE, path, std::move(handler));
}

http::Server &http::Server::Options(const std::string &path, http::Server::Handler &handler) {
    return insertHandler(RequestType::OPTIONS, path, handler);
}

http::Server &http::Server::Options(const std::string &path, http::Server::Handler &&handler) {
    return insertHandler(RequestType::OPTIONS, path, std::move(handler));
}

http::Server &http::Server::Head(const std::string &path, http::Server::Handler &handler) {
    return insertHandler(RequestType::HEAD, path, handler);
}

http::Server &http::Server::Head(const std::string &path, http::Server::Handler &&handler) {
    return insertHandler(RequestType::HEAD, path, std::move(handler));
}

