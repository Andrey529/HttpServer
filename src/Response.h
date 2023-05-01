#ifndef HTTPSERVER_RESPONSE_H
#define HTTPSERVER_RESPONSE_H

#include <string>
#include <map>

#include "Detail.h"
#include "ResponseStatusCode.h"

namespace http {
    class Response {
    public:
        using Headers = std::multimap<std::string, std::string, http::detail::StringsComparator>;

        std::string version_;
        ResponseStatusCode statusCode_;
        Headers headers_;
        std::string body_;
        std::string location_;

    private:
        size_t contentLength_ = 0;
    public:
        Response() = default;
        Response(const std::string &version, const ResponseStatusCode &statusCode, const Headers &headers,
                 const std::string &body, const std::string &location, const size_t &contentLength)
                 : version_(version), statusCode_(statusCode), headers_(headers), body_(body),
                   location_(location), contentLength_(contentLength) { }
        Response(const Response &) = default;
        Response& operator=(const Response &) = default;
        Response(Response &&) = default;
        Response& operator=(Response &&) = default;
        ~Response() = default;

        bool hasHeader(const std::string &key) const;
        std::string getHeaderValue(const std::string &key) const;
        void setHeader(const std::string &key, const std::string &value);

    };
} // namespace http

#endif //HTTPSERVER_RESPONSE_H
