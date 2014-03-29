/**
 * 7. Do serwera z poprzedniego zadania dodaj wyświetlanie informacji o adresie IP klienta, który skorzystał z usługi.
 */

#include "../lib/libnetutils.h"

#define PORT 13
#define MAX_QUEUE 128

int main () {
    int sock_id;

    printf("=== create server ===\n\n");

    /* create socket */
    sock_id = create_socket_tcp();

    /* bind server to defined port */
    bind_port(sock_id, PORT);

    /* server waiting for client */
    listen_for_client_tcp(sock_id, MAX_QUEUE);

    /* handle client */
    handle_incoming_client(sock_id, 0);

    return 0;
}
