#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "server.h"
#include <string.h>
#include <stdlib.h>

struct server server_constructor(int domain, int port, int service, // fyller i parametrarna i structen
    int protocol, int backlog, u_long interface, void (*launch)(struct server *server1)) {

    struct server server1;

    server1.domain = domain;
    server1.service = service;
    server1.port = port;
    server1.protocol = protocol;
    server1.backlog = backlog;

    server1.address.sin_family = domain; //hämtar vilken ip version(IPV4)
    server1.address.sin_port = htons(port); //hämtar vilken port
    server1.address.sin_addr.s_addr = htonl(interface); 

//---------------------------------------------------

    server1.socket = socket(domain, service, protocol);
    if (server1.socket < 0) {
        perror("Failed to initialize/connect to socket...\n");
        exit(EXIT_FAILURE);
    }

    if (bind(server1.socket, (struct sockaddr*)&server1.address, sizeof(server1.address)) < 0) {
        perror("Failed to bind socket...\n");
        exit(EXIT_FAILURE);
    }

    if (listen(server1.socket, server1.backlog) < 0) {
        perror("Failed to start listening...\n");
        exit(EXIT_FAILURE);
    }

    server1.launch = launch;
    return server1;
}

//------------------------------------------------------

void launch(struct server *server1) {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("=== WAITING FOR CONNECTION === \n");

        socklen_t addrlen = sizeof(server1->address);
        int new_socket = accept(server1->socket, (struct sockaddr*)&server1->address, &addrlen);

        ssize_t bytesRead = read(new_socket, buffer, BUFFER_SIZE - 1);

        if (bytesRead >= 0) {
            buffer[bytesRead] = '\0';  // Null terminate the string
            puts(buffer);
        } else {
            perror("Error reading buffer...\n");
        }

        char *response = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: text/html; charset=UTF-8\r\n\r\n"
                         "<!DOCTYPE html>\r\n"
                         "<html>\r\n"
                         "<head>\r\n"
                         "<title>Testing Basic HTTP-SERVER</title>\r\n"
                         "</head>\r\n"
                         "<body>\r\n"
                         "Tjo fan välkommen!\r\n"
                         "</body>\r\n"
                         "</html>\r\n";

        write(new_socket, response, strlen(response));
        close(new_socket);
    }
}
