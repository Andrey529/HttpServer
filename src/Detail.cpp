#include "Detail.h"

bool http::detail::StringsComparator::operator()(const std::string &s1, const std::string &s2) const {
    return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(),
                                        s2.end(),
                                        [](unsigned char c1, unsigned char c2) {
                                            return ::tolower(c1) < ::tolower(c2);
                                        });
}

bool http::detail::hasHeader(const http::detail::Headers &headers, const std::string &key) {
    return headers.contains(key);
}

std::string http::detail::getHeaderValue(const Headers &headers, const std::string &key) {
    for(const auto & header : headers) {
        if (header.first == key) {
            return header.second;
        }
    }
    return "";
}

void http::detail::setHeader(http::detail::Headers &headers, const std::string &key, const std::string &value) {
    headers.emplace(key, value);
}
