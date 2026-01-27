#ifndef server_h //kollar ifall ett specefikt makro inte definerat  
#define server_h

#include <netinet/in.h> //definitioner och datastrukturer för ipv4 & ipv6
#define BUFFER_SIZE 16000




struct server{
    int domain; // AF_INET = IPv4
    int port; // htons(8080) 
    int service;
    int protocol; //tcp
    int backlog;
    u_long interface;// u_long = heltal 0 - väldigt höga nummer


    int socket; // ip address + port nummer = kommunikationsväg
    struct sockaddr_in address; // Används för IPv4-adresser. Den innehåller portnummer (sin_port) och IP-adressen (sin_addr).

     
    void (*launch)(struct server *server); 
}; 

struct server server_constructor(int domain, int port, int service, int protocol, int backlog, u_long interface, void (*launch)(struct server *server));
void launch(struct Server *server);

#endif