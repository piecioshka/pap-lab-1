/**
 * 8. Uruchom własny serwer usługi time w trybie demona. Jakie modyfikacje musisz wykonać?
 */

#include "../lib/libnetutils.h"

#define PORT 13
#define MAX_QUEUE 128

int main () {
    /* test_console_lib(); */
    int sock_id;
    struct sockaddr_in address;

    /* run server as daemon */
    demonize();

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
