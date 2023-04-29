#ifndef HTTPSERVER_NETDETAIL_H
#define HTTPSERVER_NETDETAIL_H

#include <netdb.h>
#include <cstdlib>
#include <sys/wait.h>

#include <string>
#include <map>

namespace http::detail::net {
    void *get_in_addr(struct sockaddr *sa);
    void sigchld_handler(int);
} // namespace http::detail::net

#endif //HTTPSERVER_NETDETAIL_H
