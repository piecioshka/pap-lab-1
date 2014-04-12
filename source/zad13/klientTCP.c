/**
 * 13. Napisz prostą aplikację do pobierania z serwera informacji o systemie.
 * Klient łączy się z serwerem na określonym porcie.
 * Serwer przesyła do klienta wynik polecenia uptime.
 */

#include "../lib/libnetutils.h"

#define PORT 33
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
