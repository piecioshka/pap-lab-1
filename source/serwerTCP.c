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

#define MAX_BACKLOG		5
#define MAX_BUFFER		128

void handle_client(int connection_descriptor);

int main (int argc, char *argv[]) {
  int server_descriptor, connection_descriptor, daytime_port;
  struct sockaddr_in servaddr;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }

  daytime_port = atoi(argv[1]);

  server_descriptor = socket(AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(daytime_port);

  bind(server_descriptor, (struct sockaddr *) & servaddr, sizeof(servaddr));

  listen(server_descriptor, MAX_BACKLOG);

  while ( 1 ) {
    connection_descriptor = accept(server_descriptor, (struct sockaddr *) NULL, NULL);

    if (connection_descriptor >= 0) {
      handle_client(connection_descriptor);
    }
  }
}

void handle_client (int connection_descriptor) {
  char timebuffer[MAX_BUFFER + 1];
  time_t current_time;

  current_time = time(NULL);
  snprintf(timebuffer, MAX_BUFFER, "%s\n", ctime(&current_time));

  /* client welcome message */
  printf("Client\n");

  write(connection_descriptor, timebuffer, strlen(timebuffer));
  close(connection_descriptor);
}

