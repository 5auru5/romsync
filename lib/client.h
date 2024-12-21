#ifndef CLIENT_H
#define CLIENT_H

#define PORT 6767

#include <sys/socket.h>
#include "connection.h"

typedef struct Client {
    struct Connection *connection;
    char *clientId;
    int socket_fd;


} Client;

int create_client_connection(Client client);
int teardown_client_connection(Client client);

char* send_message(Client* client, char* message);

#endif
