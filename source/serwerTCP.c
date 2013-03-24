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

void HandleClient(int connectionFd);

int main ( int argc, char *argv[])
{
  int serverFd, connectionFd;
  struct sockaddr_in servaddr;
  int daytimePort;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
    exit(1);
  }
  daytimePort=atoi(argv[1]);

  serverFd = socket(AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(daytimePort);

  bind(serverFd, (struct sockaddr *)&servaddr, 
        sizeof(servaddr));

  listen(serverFd, MAX_BACKLOG);

  while ( 1 ) {

    connectionFd = accept(serverFd, 
                           (struct sockaddr *)NULL, NULL);
    if (connectionFd >= 0) {
      HandleClient(connectionFd);
    }
  }
}
void HandleClient(int connectionFd)
{
  char timebuffer[MAX_BUFFER+1];
  time_t currentTime;
  currentTime = time(NULL);
  snprintf(timebuffer, 
           MAX_BUFFER, "%s\n", ctime(&currentTime));
  write(connectionFd, timebuffer, strlen(timebuffer));
  close(connectionFd);
}

