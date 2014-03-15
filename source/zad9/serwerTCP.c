/**
 * 9. Zmodyfikuj serwer z poprzedniego zadania tak, aby można było uruchamiać go w dwóch trybach:
 * interakcyjnym (przyłączony do terminala) lub jako demon (funkcja daemon).
 *
 * Jak sprawdzić, że serwer pracuje w trybie demona?
 *   - Wprowadź możliwość zamykania serwera (za pomocą sygnału).
 *   - W trybie interakcyjnym informacja o pracy serwera jest wyświetlana na ekranie.
 *   W trybie demona informacja jest przesyłana do pliku logu. Załóż, że serwer współpracuje z programem syslog.
 *   Potrzebne funkcje:
 *
 *   #include <syslog.h>
 *   void openlog(const char *ident, int option, int facility);
 *   void syslog(int priority, const char *format, ...);
 *   void closelog(void);
 *
 *   Informacje, które powinny znaleźć się w logu:
 *   - uruchomienie serwera
 *   - nawiązane połączenia – adres IP klienta
 *   - zamknięcie serwera.
 */

#include "../lib/libnetutils.h"
#include <syslog.h>

#define PORT 13
#define MAX_QUEUE 128

int is_daemon = 0;

void sigint_handler(int status) {
    if (is_daemon) {
        syslog(LOG_NOTICE, "Successfully shutdown daemon");
        /* zamykamy komunikację z serwerem syslog */
        closelog();
    } else {
        printf("Kończymy działanie programu\n");
        fflush(stdout);
    }
    /* wyłączamy aplikację */
    exit(1);
}

void create_daemon() {
    demonize();
    openlog("serwerTCP", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
    syslog(LOG_NOTICE, "Successfully started daemon");
}

int main (int argc, char * argv[]) {
    /* availability options */
    char * opts = "d";
    /* processed option */
    int c;

    int sock_id;
    struct sockaddr_in address;

    /* dodanie handlera na SIGINT */
    signal(SIGINT, sigint_handler);

    /* check if define more than one option */
    if (argc == 2) {
        /* iteration by each of option */
        while ((c = getopt(argc, argv, opts)) != -1) {
            switch (c) {
                /* for 'u' run daemon */
                case 'd':
                    create_daemon();
                    break;
                /* for unrecognized option */
                case '?':
                default:
                    printf("Ignore passed options\n");
            }
        }
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    memset( &( address.sin_zero ), '\0', 8 );

    printf("=== create server ===\n\n");

    /* create socket */
    sock_id = create_socket_tcp();

    /* bind server to defined port */
    bind_port(sock_id, address);

    /* server waiting for client */
    listen_for_client(sock_id, MAX_QUEUE);

    /* handle client */
    handle_incoming_client(sock_id, 1);

    return 0;
}
