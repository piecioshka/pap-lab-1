/**
 * 5. Skompiluj programy klientTCP.c i serwerTCP.c z pliku lab1.tar.gz. Są to programy implementujące usługę daytime. Sprawdź czy działają poprawnie.
 * a) Najpierw sprawdź klienta ze standardową usługą daytime uruchamianą z xinetd.
 * b) Następnie sprawdź działanie całej aplikacji (serwera i klienta).
 * c) Uzupełnij programy klienta i serwera o obsługę błędów.
 */

#include "../lib/libnetutils.h"

#define PORT 13
#define MAX_QUEUE 128

int main () {
    /* test_console_lib(); */
    int sock_id;
    struct sockaddr_in address;

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
    handle_incoming_client(sock_id);

    return 0;
}

