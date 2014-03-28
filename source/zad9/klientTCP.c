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

#define PORT 13
#define DESC_IP "127.0.0.1"

int main () {
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
