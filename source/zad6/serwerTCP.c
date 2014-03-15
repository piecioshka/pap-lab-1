/**
 * 6. Napisz swoją wersję klienta i serwera standardowej usługi time
 * w wersji TCP (opis usługi time jest zawarty w RFC 868 - www.rfc-editor.org).
 * a) Najpierw opracuj klienta usługi, który będzie się łączył z usługą time uruchamianą z xinetd.
 * b) Następnie opracuj serwer usługi time.
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
    handle_incoming_client(sock_id, 0);

    return 0;
}

