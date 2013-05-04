/* utilities functions */

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>

#define MAX_BUFFER 128

void test_console_lib () {
    printf("library \"console.h\" is exists!\n");
}

int create_socket (int family) {
    int socket_id;

    /* run socket function */
    socket_id = socket(AF_INET, family, 0);

    /* if error occur - send message to user */
    if (socket_id == -1) {
        fprintf(stderr, "ERROR: unable to create socket: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
        return socket_id;
    }

    printf("create socket %d\n", socket_id);

    return socket_id;
}

int create_socket_udp () {
    return create_socket(SOCK_DGRAM);
}

int create_socket_tcp () {
    return create_socket(SOCK_STREAM);
}

int create_connection (int socket, struct sockaddr_in address) {
    int connect_status;
    struct in_addr client_ip = address.sin_addr;
    char * ip = inet_ntoa(client_ip);
    unsigned short port = ntohs(address.sin_port);

    printf("try to connecting %s:%d...\n", ip, port);

    connect_status = connect(socket, (struct sockaddr *) & address, sizeof(struct sockaddr));

    if (connect_status == -1) {
        fprintf(stderr, "ERROR: unable to create connection to socket %d: %s\n", socket, strerror(errno));
        exit(EXIT_FAILURE);
        return connect_status;
    }

    printf("connected with socket %d\n", socket);

    return connect_status;
}

int close_connection (int socket) {
     int status = close(socket);

     if (status == -1) {
        fprintf(stderr, "ERROR: unable to close connection for socket %d: %s\n", socket, strerror(errno));
        exit(EXIT_FAILURE);
        return status;
     }

     printf("close connection with socket %d\n", socket);

     return status;
}

int bind_port (int socket, struct sockaddr_in address) {
    int bind_status = bind(socket, (struct sockaddr *) & address, sizeof(struct sockaddr));
    unsigned short port = ntohs(address.sin_port);

    if (bind_status == -1) {
        fprintf(stderr, "ERROR: unable to bind port %d: %s\n", port, strerror(errno));
        exit(EXIT_FAILURE);
        return bind_status;
    }

    printf("bind port %d\n", port);

    return bind_status;
}

int listen_for_client (int socket, int backlog) {
    int listen_status = listen(socket, backlog);

    if (listen_status == -1) {
        fprintf(stderr, "ERROR: unable to bind for socket %d with backlog %d: %s\n", socket, backlog, strerror(errno));
        exit(EXIT_FAILURE);
        return listen_status;
    }

    printf("listening for socket %d with backlog %d\n", socket, backlog);

    return listen_status;
}

void receive_from_server (int socket) {
    int in;
    char buffer[MAX_BUFFER + 1];

    /* get data from client */
    while ( (in = read(socket, buffer, MAX_BUFFER)) > 0 ) {
        buffer[in] = 0;
        printf("\n%s", buffer);
    }
}

void send_to_client (int socket) {
    char time_buffer[MAX_BUFFER + 1];
    time_t current_time;

    current_time = time(NULL);
    snprintf(time_buffer, MAX_BUFFER, "%s\n", ctime(&current_time));

    write(socket, time_buffer, strlen(time_buffer));
}

void handle_incoming_client (int socket) {
    int fresh_socket, close_status;
    struct sockaddr_in address;
    socklen_t address_len = sizeof(struct sockaddr_in);
    struct in_addr client_ip;
    char * ip;
    unsigned short port;

    while ( 1 ) {
        /* accept connection with client from from queue */
        fresh_socket = accept(socket, (struct sockaddr *) & address, & address_len);
        client_ip = address.sin_addr;
        ip = inet_ntoa(client_ip);
        port = ntohs(address.sin_port);

        if (fresh_socket == -1) {
            fprintf(stderr, "ERROR: unable to accept client %s:%d: %s\n", ip, port, strerror(errno));
            exit(EXIT_FAILURE);
        }

        printf("accept client %s:%d\n", ip, port);

        /* send message to client */
        send_to_client(fresh_socket);

        /* close connection with client */
        close_status = close(fresh_socket);

        if (close_status == -1) {
            fprintf(stderr, "ERROR: unable to close connection with client %s:%d: %s\n", ip, port, strerror(errno));
            exit(EXIT_FAILURE);
        }

        printf("close client %s:%d\n\n", ip, port);
    }
}

void demonize () {
    pid_t pid, sid;
    
    /* check if already is daemon */
    if ( getppid() == 1 ) {
        fprintf(stderr, "ERROR: unable to demonize, becouse is already daemon\n");
        exit(EXIT_FAILURE);
    }
    
    /* fork current process */
    pid = fork();
    
    if (pid < 0) {
        fprintf(stderr, "ERROR: unable to demonize: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
    
    /* create a new SID for the child process */
    sid = setsid();
    
    if (sid < 0) {
        fprintf(stderr, "ERROR: unable to create new SID: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    
}