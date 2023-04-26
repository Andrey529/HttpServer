//#include <sys/socket.h>
//#include <sys/types.h>
//#include <netdb.h>
//#include <arpa/inet.h>
//#include <cstring>
//#include <string>
//#include <iostream>
//
//int main(int argc, char *argv[]) {
//    int status;
//    struct addrinfo hints;
//    struct addrinfo *servinfo;
//
//    std::memset(&hints, 0, sizeof(hints));
//    hints.ai_family = AF_UNSPEC;
//    hints.ai_socktype = SOCK_STREAM;
//    hints.ai_flags = AI_PASSIVE;
//
//    std::string port = "8080";
//    std::string address = "www.example.com";
//
//    status = getaddrinfo(address.c_str(), port.c_str(), &hints, &servinfo);
//
//    if (status != 0) {
//        std::cerr << "getaddrinfo error: " << gai_strerror(status) << '\n';
//    }
//
//    int socketFileDescriptor = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
//
//    bind(socketFileDescriptor, servinfo->ai_addr, servinfo->ai_addrlen);
//
//
//    freeaddrinfo(servinfo);
//    return 0;
//}

//
//#include "httplib.h"
//
//int main() {
//    httplib::Server server;
//
//    server.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
//        res.set_content("Hello World!", "text/plain");
//    });
//
//    server.listen("0.0.0.0", 8080);
//
//    return 0;
//}


//
//
//#include <iostream>
//#include <cstdio>
//#include <sys/socket.h>
//#include <arpa/inet.h>
//#include <cstdlib>
//#include <string>
//#include <sstream>
//#include <unistd.h>
//
//namespace
//{
//    const int BUFFER_SIZE = 30720;
//
//    void log(const std::string &message)
//    {
//        std::cout << message << std::endl;
//    }
//
//    void exitWithError(const std::string &errorMessage)
//    {
//        log("ERROR: " + errorMessage);
//        exit(1);
//    }
//}
//
//namespace http
//{
//
//    class TcpServer
//    {
//    public:
//        TcpServer(std::string ip_address, int port);
//        ~TcpServer();
//        void startListen();
//
//    private:
//        std::string m_ip_address;
//        int m_port;
//        int m_socket;
//        int m_new_socket;
//        long m_incomingMessage;
//        struct sockaddr_in m_socketAddress;
//        unsigned int m_socketAddress_len;
//        std::string m_serverMessage;
//
//        int startServer();
//        void closeServer();
//        void acceptConnection(int &new_socket);
//        std::string buildResponse();
//        void sendResponse();
//    };
//
//
//    TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(),
//                                                             m_incomingMessage(),
//                                                             m_socketAddress(), m_socketAddress_len(sizeof(m_socketAddress)),
//                                                             m_serverMessage(buildResponse())
//    {
//        m_socketAddress.sin_family = AF_INET;
//        m_socketAddress.sin_port = htons(m_port);
//        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
//
//        if (startServer() != 0)
//        {
//            std::ostringstream ss;
//            ss << "Failed to start server with PORT: " << ntohs(m_socketAddress.sin_port);
//            log(ss.str());
//        }
//    }
//
//    TcpServer::~TcpServer()
//    {
//        closeServer();
//    }
//
//    int TcpServer::startServer()
//    {
//        m_socket = socket(AF_INET, SOCK_STREAM, 0);
//        if (m_socket < 0)
//        {
//            exitWithError("Cannot create socket");
//            return 1;
//        }
//
//        if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0)
//        {
//            exitWithError("Cannot connect socket to address");
//            return 1;
//        }
//
//        return 0;
//    }
//
//    void TcpServer::closeServer()
//    {
//        close(m_socket);
//        close(m_new_socket);
//        exit(0);
//    }
//
//    void TcpServer::startListen()
//    {
//        if (listen(m_socket, 20) < 0)
//        {
//            exitWithError("Socket listen failed");
//        }
//
//        std::ostringstream ss;
//        ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
//        log(ss.str());
//
//        int bytesReceived;
//
//        while (true)
//        {
//            log("====== Waiting for a new connection ======\n\n\n");
//            acceptConnection(m_new_socket);
//
//            char buffer[BUFFER_SIZE] = {0};
//            bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);
//            if (bytesReceived < 0)
//            {
//                exitWithError("Failed to read bytes from client socket connection");
//            } else {
//                std::cout << buffer << std::endl;
//            }
//
//            std::ostringstream ss;
//            ss << "------ Received Request from client ------\n\n";
//            log(ss.str());
//
//            sendResponse();
//
//            close(m_new_socket);
//        }
//    }
//
//    void TcpServer::acceptConnection(int &new_socket)
//    {
//        new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
//        if (new_socket < 0)
//        {
//            std::ostringstream ss;
//            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
//            exitWithError(ss.str());
//        }
//    }
//
//    std::string TcpServer::buildResponse()
//    {
//        std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
//        std::ostringstream ss;
//        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
//           << htmlFile;
//
//        return ss.str();
//    }
//
//    void TcpServer::sendResponse()
//    {
//        long bytesSent;
//
//        bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());
//
//        if (bytesSent == m_serverMessage.size())
//        {
//            log("------ Server Response sent to client ------\n\n");
//        }
//        else
//        {
//            log("Error sending response to client");
//        }
//    }
//
//} // namespace http
//
//int main() {
//    http::TcpServer tcpServer("127.0.0.1", 1234);
//    tcpServer.startListen();
//}


#include "HttpServer.h"

int main() {
    http::HttpServer server("127.0.0.1", 1234);
}