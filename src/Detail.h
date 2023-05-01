#ifndef HTTPSERVER_DETAIL_H
#define HTTPSERVER_DETAIL_H

#include <string>
#include <map>

namespace http::detail {
    struct StringsComparator {
        bool operator()(const std::string &s1, const std::string &s2) const;
    };

    using Headers = std::multimap<std::string, std::string, StringsComparator>;

    bool hasHeader(const Headers &headers, const std::string &key);
    std::string getHeaderValue(const Headers &headers, const std::string &key);
    void setHeader(Headers &headers, const std::string &key, const std::string &value);
} // namespace http::detail

#endif //HTTPSERVER_DETAIL_H
