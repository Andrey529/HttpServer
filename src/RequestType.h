#ifndef HTTPSERVER_REQUESTTYPE_H
#define HTTPSERVER_REQUESTTYPE_H

namespace http {

    enum class RequestType {
        GET,
        POST,
        UPDATE,
        DELETE,
        OPTIONS
    };

} // namespace http

#endif //HTTPSERVER_REQUESTTYPE_H
