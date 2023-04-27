#ifndef HTTPSERVER_DETAIL_H
#define HTTPSERVER_DETAIL_H

#include <netdb.h>
#include <cstdlib>
#include <sys/wait.h>

namespace http::detail {
    void *get_in_addr(struct sockaddr *sa);
    void sigchld_handler(int);

} // namespace http::detail

#endif //HTTPSERVER_DETAIL_H
