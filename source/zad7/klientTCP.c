/**
 * 7. Do serwera z poprzedniego zadania dodaj wyświetlanie informacji o adresie IP klienta, który skorzystał z usługi.
 */

#include "../lib/libnetutils.h"

#define PORT 13
#define DESC_IP "127.0.0.1"

int main () {
    /* test_console_lib(); */
    int sock_id;
    struct sockaddr_in address;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(DESC_IP);
    address.sin_port = htons(PORT);
    memset( &( address.sin_zero ), '\0', 8 );

    printf("=== create client instance ===\n\n");

    /* create socket to connection */
    sock_id = create_socket_tcp();

    /* use create socket to connect address */
    create_connection(sock_id, address);

    /* receive data from server */
    receive_from_server(sock_id);

    /* close connection */
    close_connection(sock_id);

    return 0;
}