/**
 * 14. Aplikacja echo
 * a) Opracuj klienta standardowej usługi echo w wersji TCP (opis usługi echo jest zawarty w RFC 862 - www.rfc-editor.org).
 *  Niech korzysta on z serwera echo uruchomionego za pomocą xinetd.
 *  Aplikacja ma umożliwiać wprowadzanie danych przesyłanych do serwera do momentu wygenerowania przez użytkownika końca pliku (CTRL-D).
 *  Dane serwera mają być podawane w postaci nazwy lub adresu IP, nazwy lub portu usługi.
 *  Problemy do rozwiązania: Czy klient powinien od razu wyświetlać otrzymaną część tekstu czy też czekać na zwrócenie przez serwer całego tekstu?
 *  Jak sprawdzić czy klient otrzymał od serwera cały tekst?
 *  Klient powinien przed próbą połączenia wyświetlić komunikat:
 *  "Nawiazywane polaczenie z adres_IP na porcie numer_Portu ...".
 *  W miejscu adres_IP należy wyświetlać właściwy adres IP, i odpowiednio w miejscu numer_Portu – numer portu.
 *  Po nawiązaniu połączenia należy wyświetlić komunikat:
 *  "Polaczenie nawiazano. Wprowadz tekst."
 * b) Sprawdź działanie klienta przy zablokowanej i odblokowanej usłudze echa na serwerze. Uzupełnij klienta o obsługę błędów.
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
