/**
 * 5. Skompiluj programy klientTCP.c i serwerTCP.c z pliku lab1.tar.gz.
 * Są to programy implementujące usługę daytime. Sprawdź czy działają poprawnie.
 * a) Najpierw sprawdź klienta ze standardową usługą daytime uruchamianą z xinetd.
 * b) Następnie sprawdź działanie całej aplikacji (serwera i klienta).
 * c) Uzupełnij programy klienta i serwera o obsługę błędów.
 *
 *  Daytime Server (TCP)
 */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

/* max number of client connection at the same time */
#define MAX_BACKLOG		5
#define MAX_BUFFER		128

void handle_client (int);
void get_client_ip_address (int);
void sig_handler(int);

static void daemonize(void);
static int is_daemon = 0;

int main (int argc, char *argv[]) {
    int server_descriptor, connection_descriptor, daytime_port;
    struct sockaddr_in server_address, cli_addr;
    struct in_addr cli_ip;
    socklen_t clilen;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }

    /* get port from param and convert this string to integer */
    daytime_port = atoi(argv[1]);

    /* get mode -d - is_daemon */

    if (argc == 3 && (strcmp(argv[2],"-d") == 0)) {
        daemonize();
        is_daemon = 1;
        openlog("serwerTCP", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
        syslog(LOG_NOTICE, "Successfully started is_daemon");
    }

    signal(SIGTERM, sig_handler);
    signal(SIGINT, sig_handler);

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
    clilen = sizeof(cli_addr);

    while ( 1 ) {
        connection_descriptor = accept(server_descriptor, (struct sockaddr *) & cli_addr, &clilen);
        cli_ip = cli_addr.sin_addr;
        if (is_daemon == 1){
            syslog (LOG_NOTICE, "Client IP address is: %s", inet_ntoa(cli_ip));
        } else {
            printf("Client IP address is: %s\n", inet_ntoa(cli_ip));
        }
        if (connection_descriptor >= 0) {
            /* get_client_ip_address (connection_descriptor); */
            handle_client(connection_descriptor);
        }
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

static void daemonize (void) {
    pid_t pid, sid;
    int fd;

    /* already a is_daemon */
    if ( getppid() == 1 ) return;

    /* fork off the parent process */
    pid = fork();
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS); /* killing the parent process */
    }

    /* at this point we are executing as the child process */

    /* create a new SID for the child process */
    sid = setsid();

    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    /* change the current working directory */
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }

    fd = open("/dev/null",O_RDWR, 0);

    if (fd != -1) {
        dup2 (fd, STDIN_FILENO);
        dup2 (fd, STDOUT_FILENO);
        dup2 (fd, STDERR_FILENO);

        if (fd > 2) {
            close (fd);
        }
    }

    /* resetting file creation mask */
    umask(027);
}

void sig_handler (int sig) {
    switch (sig) {
    case SIGTERM:
        if (is_daemon == 1){
            syslog (LOG_NOTICE, "Daemon has been stopped with SIGTERM");
        } else {
            printf("Daemon has been stopped with SIGTERM");
        }
        closelog();
        exit(EXIT_SUCCESS);
    case SIGINT:
        if (is_daemon == 1){
            syslog (LOG_NOTICE, "Daemon has been stopped with SIGINT");
        } else {
            printf("Daemon has been stopped with SIGINT");
        }
        closelog();
        exit(EXIT_SUCCESS);
    default:
        syslog (LOG_NOTICE, "wasn't expecting that!");
        closelog();
        exit(EXIT_SUCCESS);
    }
}

