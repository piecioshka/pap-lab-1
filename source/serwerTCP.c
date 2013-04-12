/*
 *  Daytime Server (TCP)
 */
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* max number of client connection at the same time */
#define MAX_BACKLOG		5
#define MAX_BUFFER		128

void handle_client (int connection_descriptor);
void get_client_ip_address (int connection_descriptor);

int main (int argc, char *argv[]) {
  int server_descriptor, connection_descriptor, daytime_port;
  struct sockaddr_in server_address;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }

  /* get port from param and convert this string to integer */
  daytime_port = atoi(argv[1]);

  /* create socket */
  server_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  /* set local IP address and port, which is sets by parameter */
  memset(&server_address, 0, sizeof(server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port = htons(daytime_port);

  /* set local protocol address to socket */
  bind(server_descriptor, (struct sockaddr *) & server_address, sizeof(server_address));

  /* set server mode to listen clients */
  listen(server_descriptor, MAX_BACKLOG);

  while ( 1 ) {
    connection_descriptor = accept(server_descriptor, (struct sockaddr *) NULL, NULL);

    if (connection_descriptor >= 0) {
      /* get_client_ip_address (connection_descriptor); */
      handle_client(connection_descriptor);
    }
  }
}

void get_client_ip_address (int connection_descriptor) {
  int in;
  char buffer[MAX_BUFFER + 1];

  while ( (in = read(connection_descriptor, buffer, MAX_BUFFER)) > 0) {
    buffer[in] = 0;
    printf("\n%s", buffer);
    break;
  }
}

void handle_client (int connection_descriptor) {
  char time_buffer[MAX_BUFFER + 1];
  time_t current_time;

  current_time = time(NULL);
  snprintf(time_buffer, MAX_BUFFER, "%s\n", ctime(&current_time));

  write(connection_descriptor, time_buffer, strlen(time_buffer));
  close(connection_descriptor);
}

