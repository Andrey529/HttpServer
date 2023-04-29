#include "Request.h"

bool Request::hasHeader(const std::string &key) const {
    return http::detail::hasHeader(headers_, key);
}

std::string Request::getHeaderValue(const std::string &key) const {
    return http::detail::getHeaderValue(headers_, key);
}

void Request::setHeader(const std::string &key, const std::string &value) {
    http::detail::setHeader(headers_, key, value);
}
