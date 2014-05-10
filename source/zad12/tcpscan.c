/**
 * 12. Napisz program, który będzie skanował określone porty korzystając z połączenia TCP (TCP connect scan).
 * Zakres badanych portów jest podawany w wywołaniu programu.
 *
 * Przykład działania programu:
 * $ ./tcpscan sz133 1 1000
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define PORT_NUMBERS 65536

void throw_bad_params() {
    fprintf(stderr, "ERROR: Niepoprawna liczba parametrów\n");
    fprintf(stderr, "Użycie: ./tcpscan.o HOST [PORT_START=0] [PORT_END=65535]\n");
    exit(EXIT_FAILURE);
}

char * resolve_domain(char * domain) {
    struct hostent * he;
    struct in_addr **addr_list;
    char * ip = "";

    if ((he = gethostbyname(domain)) != NULL) {
        addr_list = (struct in_addr **)he->h_addr_list;
        ip = inet_ntoa(*addr_list[0]);
    }

    return ip;
}

int check_connection(char * host, int port) {
    int status;
    int socket_id;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(host);
    address.sin_port = htons(port);
    memset( &( address.sin_zero ), '\0', 8 );

    socket_id = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_id == -1) {
        fprintf(stderr, "ERROR: unable to create socket: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    status = connect(socket_id, (struct sockaddr *) & address, sizeof(struct sockaddr));

    if (close(socket_id) == -1) {
        fprintf(stderr, "ERROR: unable to close connection for socket %d: %s\n", socket_id, strerror(errno));
        exit(EXIT_FAILURE);
    }

    return status;
}

char * resolve_number(int serv_port, char * proto) {
    int number = htons(serv_port);
    struct servent * ent;
    char * name = "uknown";

    if ((ent = getservbyport(number, proto)) != NULL) {
        name = ent->s_name;
    }

    return name;
}

void scan_tcp(char * host, int start_port, int end_port) {
    int port;
    printf("Running scan...\n");

    host = resolve_domain(host);

    if (strlen(host) == 0) {
        fprintf(stderr, "ERROR: Host nie odnaleziony\n");
        exit(EXIT_FAILURE);
    }

    for (port = start_port; port <= end_port; ++port) {
        if (check_connection(host, port) != -1) {
            printf("Open: %d (%s)\n", port, resolve_number(port, "tcp"));
        }
    }
}

int main(int argc, char * argv[]) {
    if (argc != 2 && argc != 4) {
        throw_bad_params();
    } else {
        char * host = argv[1];
        int start_port = 0;
        int end_port = PORT_NUMBERS - 1;

        if (argc == 4) {
            start_port = atoi(argv[2]);
            end_port = atoi(argv[3]);
        }
        scan_tcp(host, start_port, end_port);
    }

    return 0;
}
