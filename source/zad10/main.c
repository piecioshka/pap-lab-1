/**
 * 10. Zamiana nazwy domenowej na adres IP
 * Napisz program, który będzie działał następująco:
 *  - jeśli podasz adres IP, program wyświetli nazwę domenową.
 *  - jeśli podasz nazwę domenową, program wyświetli numer IP.
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

void resolve_domain(char * domain) {
    struct hostent * he;
    int i;
    struct in_addr **addr_list;

    printf("Resolve domain %s\n", domain);

    if ((he = gethostbyname(domain)) == NULL) {
        fprintf(stderr, "ERROR: Bad domain name\n");
        exit(1);
    }

    addr_list = (struct in_addr **)he->h_addr_list;
    for (i = 0; addr_list[i] != NULL; i++) {
        printf("IP Address: %s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");
}

void resolve_address(char * ip) {
    struct hostent *he;
    struct in_addr ipv4addr;

    printf("Resolve ip address %s\n", ip);

    inet_pton(AF_INET, ip, &ipv4addr);
    if ((he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET)) == NULL) {
        fprintf(stderr, "ERROR: Bad IP address name\n");
        exit(1);
    }
    printf("Hostname: %s\n", he->h_name);
}

int main(int argc, char * argv[]) {
    /* availability options */
    char * opts = "d:i:";
    /* processed option */
    int c;

    if (argc < 2) {
        fprintf(stderr, "ERROR: Number of params is not enough\n");
        exit(1);
    } else {
        while ((c = getopt(argc, argv, opts)) != -1) {
            switch (c) {
                case 'd':
                    resolve_domain(optarg);
                    break;
                case 'i':
                    resolve_address(optarg);
                    break;

                /* for unrecognized option */
                case '?':
                default:
                    printf("Ignore passed options\n");
            }
        }
    }

    exit(0);
}
