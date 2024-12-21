#include "client.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int create_client_connection(Client client){
    int status;
    if ((client.socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("%s", "Could not create socket!");
        return -1;
    }

    union connectionAddr *connection_address = malloc(sizeof(union connectionAddr));
    struct Connection *connection = malloc(sizeof(struct Connection));

    connection->serv_addr.sin_family = AF_INET;
    connection->serv_addr.sin_port = PORT;

    if (inet_pton(AF_INET, connection->connection_address.hostname, &connection->serv_addr.sin_addr) <=0){
        printf("\n%s", "Invalid address! This address is not supported!");
        return -1;
    }
    if ((status = connect(client.socket_fd, (struct sockaddr*)&connection->serv_addr, sizeof(connection->serv_addr))) <0)
    {
        printf("\n%s", "Failed to make a connection!");
        return -1;
    }
    return 0;
}

int teardown_client_connection(Client client){
    return close(client.socket_fd);
}


char* send_message(Client* client, char* message){
    char* buffer = calloc(BUFFER_SIZE, sizeof(char));
    int value_read;
    send(client->socket_fd, message, strlen(message), 0 );
    value_read = read(client->socket_fd, buffer, BUFFER_SIZE-1);
    return buffer;
}

