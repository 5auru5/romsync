#ifndef CONNECTION_H
#define CONNECTION_H

#include <netinet/in.h>

union connectionAddr {
    unsigned long s_addr;
    char *hostname;
};


struct Connection{
    union connectionAddr connection_address;
    short int port;
    struct sockaddr_in serv_addr;
};



#endif