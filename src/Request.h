#ifndef HTTPSERVER_REQUEST_H
#define HTTPSERVER_REQUEST_H

#include <string>
#include <map>

#include "Detail.h"

class Request {
public:
    using Headers = std::multimap<std::string, std::string, http::detail::StringsComparator>;
    std::string method_;
    std::string path_;
    std::string version_;

    Headers headers_;
    std::string body_;

    Request() = default;
    Request(const std::string &method, const std::string &path, const std::string version,
            const Headers &headers, const std::string &body)
            : method_(method), path_(path), version_(version), headers_(headers), body_(body) {}

    ~Request() = default;

//    std::string remote_addr;
//    int remote_port = -1;
//    std::string local_addr;
//    int local_port = -1;

//    std::string target;

    bool hasHeader(const std::string &key) const;
    std::string getHeaderValue(const std::string &key) const;
    void setHeader(const std::string &key, const std::string &value);
};

#endif //HTTPSERVER_REQUEST_H
