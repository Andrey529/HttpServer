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

//         spawning a new process
        if (!fork()) {
            close(fileDescriptorSocket_); // this socket does not need to be listened to, it is only needed for the parent process

            std::cout << "------ Received Request from client ------\n" << std::endl;
            // read request
            std::string requestString;
            readRequest(requestString);

            Request request;
            parseRequest(requestString, request);

            Response response;
            processRequestAndCreateResponse(request, response);

            sendResponse(response);

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
    if (handlers_.contains(requestType)) {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = handlers_.at(requestType);
        handlersWithPath.emplace_back(path, handler);
        handlers_.at(requestType) = handlersWithPath;
    } else {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = {};
        handlersWithPath.emplace_back(path, handler);
        handlers_.emplace(requestType, handlersWithPath);
    }
    return *this;
}

http::Server &http::Server::insertHandler(const http::RequestType &requestType, const std::string &path,
                                          http::Server::Handler &&handler) {
    if (handlers_.contains(requestType)) {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = handlers_.at(requestType);
        handlersWithPath.emplace_back(path, std::move(handler));
        handlers_.at(requestType) = handlersWithPath;
    } else {
        std::vector<std::pair<std::string, Handler>> handlersWithPath = {};
        handlersWithPath.emplace_back(path, std::move(handler));
        handlers_.emplace(requestType, handlersWithPath);
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

void http::Server::readRequest(std::string &requestString) {
    char buffer[bufferSize_] = {0};
    ssize_t bytesReceived = read(fileDescriptorNewSocket_, buffer, bufferSize_);
    if (bytesReceived < 0) {
        std::cout << "Failed to read bytes from client socket connection" << std::endl;

        // TODO: add handling this situation
        //  server must return 5** number of error
    } else {
        std::cout << buffer << std::endl;
        requestString = buffer;
    }
}

void http::Server::parseRequest(std::string &requestString, http::Request &request) {
    // TODO: add exception handling

    // search for the body of the request, and if it is exist, then set it
    size_t positionBody = requestString.find("\r\n\r\n");
    if (positionBody == -1) { // not find substr = "\r\n\r\n"
        positionBody = requestString.find("\n\n");
        if (positionBody != -1) { // find substr = "\n\n", request body next
            positionBody += 2;
            request.body_ = requestString.substr(positionBody);
            request.contentLength_ = request.body_.size();
            requestString.erase(positionBody);
        }
    } else { // find substr = "\r\n\r\n", request body next
        positionBody += 4;
        request.body_ = requestString.substr(positionBody);
        request.contentLength_ = request.body_.size();
        requestString.erase(positionBody);
    }


    // splitting http headers into separate lines
    std::vector<std::string> stringsFromRequest;
    std::string temp;
    for (auto it = requestString.begin(); it != requestString.end(); ++it) {
        if (*it == '\n') {
            if (!temp.empty() && temp.substr(temp.size() - 1) == "\r") {
                temp = temp.substr(0, temp.size() - 1);
            }
            if (!temp.empty()) {
                stringsFromRequest.emplace_back(temp);
                temp.clear();
            }
        } else {
            temp += *it;
        }
    }

    if (!temp.empty()) {
        stringsFromRequest.emplace_back(temp);
    }


    // parse first main request string
    request.method_ = http::stringToRequestType(stringsFromRequest[0].substr(0, stringsFromRequest[0].find(' ')));
    stringsFromRequest[0].erase(0, stringsFromRequest[0].find(' ') + 1);

    request.path_ = stringsFromRequest[0].substr(0, stringsFromRequest[0].find(' '));
    request.version_ = stringsFromRequest[0].substr(stringsFromRequest[0].find(' ') + 1);

    // parse headers
    for (size_t i = 1; i < stringsFromRequest.size(); ++i) {
        request.setHeader(stringsFromRequest[i].substr(0, stringsFromRequest[i].find(':')),
                          stringsFromRequest[i].substr(stringsFromRequest[i].find(':') + 1));
    }

    std::cout << "Request has been successfully parsed" << std::endl;
}

void http::Server::processRequestAndCreateResponse(const http::Request &request, http::Response &response) {

    response.setHeader("Server", "Andrey529/HttpServer");
    response.setHeader("Connection", "Close");

    try {
        std::string requestPath = request.path_;
        Handler handler;
        std::vector<std::pair<std::string, Handler>> handlersByRequestType = handlers_.at(request.method_);
        for (const auto &elem: handlersByRequestType) {
            if (elem.first == requestPath) {
                handler = elem.second;
            }
        }

        if (handler != nullptr) {
            response.statusCode_ = ResponseStatusCode::OK;
            response.version_ = "HTTP/1.1";
            handler(request, response);
            if (!response.body_.empty()) {
                response.setHeader("Content-Type", response.contentType_);
                response.setHeader("Content-Length", std::to_string(response.contentLength_));
            }
        } else {
            response.statusCode_ = ResponseStatusCode::NOT_FOUND; // 404
            std::string message = "<html><body><h1>Resource not found</h1></body></html>";
            response.set_content(message, "text/html; charset=utf-8");
            response.setHeader("Content-Length", std::to_string(response.contentLength_));
            response.setHeader("Content-Type", "text/html; charset=utf-8");
        }
    } catch (const std::exception &exception) {
        std::cout << "Internal server error while processing request and creating response\n" << exception.what() << std::endl;
        response.statusCode_ = ResponseStatusCode::INTERNAL_SERVER_ERROR; // 500
        response.setHeader("Content-Type", "text/html; charset=utf-8");
        std::string message("<html><body><h1>Internal server error</h1></body></html>");
        response.set_content(message, "text/html");
        response.setHeader("Content-Length", std::to_string(response.contentLength_));
    }

}

void http::Server::sendResponse(const http::Response &response) {
    // creating response
    std::string statusLine =
            response.version_ + " " + http::responseStatusCodeToStringNumber(response.statusCode_) + " " +
            http::responseStatusCodeToString(response.statusCode_) + '\n';

    std::ostringstream responseString;
    responseString << statusLine;
    for (const auto &header : response.headers_) {
        responseString << header.first << ": " << header.second << '\n';
    }

    if (!response.body_.empty()) {
        responseString << "\r\n" << response.body_;
    }

    // send response
    ssize_t bytesSent = send(fileDescriptorNewSocket_, responseString.str().c_str(), responseString.str().size(), 0);

    std::cout << "------ Server Response sent to client ------\n" << std::endl;
    std::cout << responseString.str() << '\n' << std::endl;

    if (bytesSent < 0) {
        std::cerr << "Failed to send bytes to client socket connection" << std::endl;
    }

}

