#include "Server.h"

int main() {
    http::Server server("127.0.0.1", 1234);

    server.start();
}