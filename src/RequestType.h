#ifndef HTTPSERVER_REQUESTTYPE_H
#define HTTPSERVER_REQUESTTYPE_H

#include <string>

namespace http {

    enum class RequestType {
        GET,
        POST,
        PUT,
        DELETE,
        OPTIONS,
        HEAD
    };

    std::string requestTypeToString(const RequestType &requestType);

    RequestType stringToRequestType(const std::string &str);

} // namespace http

#endif //HTTPSERVER_REQUESTTYPE_H
