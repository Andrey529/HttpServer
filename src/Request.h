#ifndef HTTPSERVER_REQUEST_H
#define HTTPSERVER_REQUEST_H

#include <string>
#include <map>

#include "Detail.h"
#include "RequestType.h"

namespace http {
    class Request {
    public:
        using Headers = std::multimap<std::string, std::string, http::detail::StringsComparator>;
        RequestType method_;
        std::string path_;
        std::string version_;

        Headers headers_;
        std::string body_;
        size_t contentLength_ = 0;

        Request() = default;
        Request(const std::string &method, const std::string &path, const std::string version,
                const Headers &headers, const std::string &body, const size_t &contentLength)
                : method_(stringToRequestType(method)), path_(path), version_(version),
                  headers_(headers), body_(body), contentLength_(contentLength) {}
        Request(const Request &) = default;
        Request& operator=(const Request &) = default;
        Request(Request &&) = default;
        Request& operator=(Request &&) = default;
        ~Request() = default;

//        std::string remote_addr;
//        int remote_port = -1;
//        std::string local_addr;
//        int local_port = -1;
//
//        std::string target;

        bool hasHeader(const std::string &key) const;
        [[nodiscard]] std::string getHeaderValue(const std::string &key) const;
        void setHeader(const std::string &key, const std::string &value);
    };
} // namespace http


#endif //HTTPSERVER_REQUEST_H
