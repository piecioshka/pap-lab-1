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

#include "../lib/libnetutils.h"

void resolve_domain(char * domain) {
    struct hostent * he;
    int i;
    struct in_addr **addr_list;

    printf("resolve domain %s\n", domain);

    if ((he = gethostbyname(domain)) == NULL) {
        fprintf(stderr, "Bad domain name\n");
        exit(1);
    }

    addr_list = (struct in_addr **)he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++) {
        printf("IP Address: %s ", inet_ntoa(*addr_list[i]));
    }
    printf("\n");
}

void resolve_address(char * ip) {
    struct hostent *he;
    struct in_addr ipv4addr;

    printf("resolve ip address %s\n", ip);

    inet_pton(AF_INET, ip, &ipv4addr);
    if ((he = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET)) == NULL) {
        fprintf(stderr, "Bad IP address name\n");
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
        fprintf(stderr, "Zbyt malo parametrów\n");
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

