#include "server.h"
#include <arpa/inet.h>

int main() {
    struct server server = server_constructor(AF_INET, 8080, SOCK_STREAM, 0, 10, INADDR_ANY, launch);
    server.launch(&server);
    return 0;
}
