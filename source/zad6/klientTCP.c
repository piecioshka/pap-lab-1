/**
 * 6. Napisz swoją wersję klienta i serwera standardowej usługi time
 * w wersji TCP (opis usługi time jest zawarty w RFC 868 - www.rfc-editor.org).
 * a) Najpierw opracuj klienta usługi, który będzie się łączył z usługą time uruchamianą z xinetd.
 * b) Następnie opracuj serwer usługi time.
 */

#include "../lib/libnetutils.h"

#define PORT 13
#define DESC_IP "127.0.0.1"

int main () {
    int sock_id;

    printf("=== create client instance ===\n\n");

    /* create socket to connection */
    sock_id = create_socket_tcp();

    /* use create socket to connect address */
    create_connection_tcp(sock_id, DESC_IP, PORT);

    /* receive data from server */
    receive_from_server(sock_id);

    /* close connection */
    close_connection(sock_id);

    return 0;
}
