/**
 * 11. Zamiana nazwy usługi na numer portu
 * Napisz program, który będzie działał następująco:
 *  - jeśli podasz numer usługi, program wyświetli jej nazwę
 *  - jeśli podasz nazwę usługi, program wyświetli jej numer
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/libnetutils.h"

void resolve_name(char * servname, char * proto) {
    int i;
    short port;
    struct servent * ent;

    printf("resolve name %s / %s\n\n", servname, proto);

    printf("querying for servname=%s, proto=%s\n", servname, proto); 

    /* get the service record */
    if((ent = getservbyname(servname, proto)) == NULL) {
        perror("getservbyname returned NULL");
        exit(1);
    }

    printf("name=%s\n", ent->s_name);

    printf("aliases:\n"); 
    for (i = 0; ent->s_aliases[i]; i++) {
        printf("  %s\n", ent->s_aliases[i]);
    }
    port = ntohs(ent->s_port);
    printf("port=%d proto=%s\n", port, ent->s_proto);
}

void resolve_number(char * number_s, char * proto) {
    int i;
    int serv_port = atoi(number_s);
    int number = htons(serv_port);
    short port;
    struct servent * ent;

    printf("resolve number %d / %s\n\n", serv_port, proto);
    printf("querying for number=%d, proto=%s\n", number, proto);

    /* get the service record */
    if((ent = getservbyport(number, proto)) == NULL) {
        perror("getservbyname returned NULL");
        exit(1);
    }

    printf("name=%s\n", ent->s_name);

    printf("aliases:\n"); 
    for (i = 0; ent->s_aliases[i]; i++) {
        printf("  %s\n", ent->s_aliases[i]);
    }
    port = ntohs(ent->s_port);
    printf("port=%d proto=%s\n", port, ent->s_proto);
}

int main(int argc, char * argv[]) {
    /* availability options */
    char * opts = "n:N:";
    /* processed option */
    int c;

    if (argc < 2) {
        fprintf(stderr, "Zbyt malo parametrów\n");
        exit(1);
    } else {
        while ((c = getopt(argc, argv, opts)) != -1) {
            switch (c) {
                case 'n':
                    resolve_name(optarg, "tcp");
                    break;
                case 'N':
                    resolve_number(optarg, "tcp");
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

