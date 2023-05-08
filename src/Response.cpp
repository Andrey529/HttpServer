#include "Response.h"

bool http::Response::hasHeader(const std::string &key) const {
    return http::detail::hasHeader(headers_, key);
}

std::string http::Response::getHeaderValue(const std::string &key) const {
    return http::detail::getHeaderValue(headers_, key);
}

void http::Response::setHeader(const std::string &key, const std::string &value) {
    http::detail::setHeader(headers_, key, value);
}

void http::Response::set_content(const std::string &content, const std::string &contentType) {
    contentType_ = contentType;
    body_ = content;
    contentLength_ = body_.size();
}
