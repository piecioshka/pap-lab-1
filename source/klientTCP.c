/*
 *  Daytime Client (TCP)
 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFFER            128
#define DAYTIME_SERVER_PORT   13

void daytime (int connection_descriptor);

int main (int argc, char *argv[]) {
    int connection_descriptor, daytime_port;
    struct sockaddr_in server_address;

    if ((argc < 2) || (argc > 3)) {
        fprintf(stderr,"Usage: %s <Server IP> [<Daytime Port>]\n", argv[0]);
        exit(1);
    }

    if (argc == 3) {
        daytime_port = atoi(argv[2]);
    } else {
        daytime_port = DAYTIME_SERVER_PORT;
    }

    connection_descriptor = socket(PF_INET, SOCK_STREAM, 0);

    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(argv[1]);
    server_address.sin_port = htons(daytime_port);

    connect(connection_descriptor, (struct sockaddr *) & server_address, sizeof(server_address));

    daytime(connection_descriptor);

    return(0);
}

void daytime (int connection_descriptor) {
    int in;
    char buffer[MAX_BUFFER + 1];

    while ( (in = read(connection_descriptor, buffer, MAX_BUFFER)) > 0 ) {
        buffer[in] = 0;
        printf("\n%s", buffer);
    }

    close(connection_descriptor);
}

