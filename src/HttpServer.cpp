#include <unistd.h>
#include "HttpServer.h"

http::HttpServer::HttpServer(const std::string &ipAddress, const int &port) : ipAddress_(ipAddress), port_(port),
                                                                              fileDescriptorSocket_(),
                                                                              fileDescriptorNewSocket_() {
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

    int connectionsCount = 20;
    status = listen(fileDescriptorSocket_, connectionsCount);
    if (status == -1) {
        std::cerr << "Error listen" << std::endl;
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

        char remoteHost[INET6_ADDRSTRLEN];
        inet_ntop(their_address.ss_family, get_in_addr((struct sockaddr *) &their_address), remoteHost,sizeof(remoteHost));
        std::cout << "Server get connection from: " << remoteHost << std::endl;

        if (!fork()) { // это порождённые процессы
            close(fileDescriptorSocket_); // его слушать не нужно
            if (send(fileDescriptorNewSocket_, "Hello, world!", 13, 0) == -1)
                perror("send");
            close(fileDescriptorNewSocket_);
            exit(0);
        }
        close(fileDescriptorNewSocket_); // родителю это не нужно
    }
}

//http::HttpServer::~HttpServer() {
//
//}

void *http::HttpServer::get_in_addr(struct sockaddr *sa) {
    return sa->sa_family == AF_INET
           ? (void *) &(((struct sockaddr_in*)sa)->sin_addr)
           : (void *) &(((struct sockaddr_in6*)sa)->sin6_addr);
}
