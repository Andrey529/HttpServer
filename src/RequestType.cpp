#include "RequestType.h"

std::string http::requestTypeToString(const http::RequestType &requestType) {
    switch (requestType) {
        case RequestType::GET: return "GET";
        case RequestType::POST: return "POST";
        case RequestType::PUT: return "PUT";
        case RequestType::DELETE: return "DELETE";
        case RequestType::OPTIONS: return "OPTIONS";
        case RequestType::HEAD: return "HEAD";
    }
}

http::RequestType http::stringToRequestType(const std::string &str) {
    if (str == "GET") return RequestType::GET;
    else if (str == "POST") return RequestType::POST;
    else if (str == "PUT") return RequestType::PUT;
    else if (str == "DELETE") return RequestType::DELETE;
    else if (str == "OPTIONS") return RequestType::OPTIONS;
    else if (str == "HEAD") return RequestType::HEAD;
}
