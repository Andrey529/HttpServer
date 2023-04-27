#include "Detail.h"

namespace http::detail {
    void *get_in_addr(struct sockaddr *sa) {
        return sa->sa_family == AF_INET
               ? (void *) &(((struct sockaddr_in *) sa)->sin_addr)
               : (void *) &(((struct sockaddr_in6 *) sa)->sin6_addr);
    }
    void sigchld_handler(int) {
        while(waitpid(-1, nullptr, WNOHANG) > 0);
    }

} // namespace http::detail
