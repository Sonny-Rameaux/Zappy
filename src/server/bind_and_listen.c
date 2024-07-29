/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** bind_and_listen
*/
#include "server.h"

int has_all_digits(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) {
            my_putstr_fd("The string contains non-digit characters\r\n", 2);
            return 0;
        }
    }
    return 1;
}

int bind_socket(int s, par_t *parsing)
{
    struct sockaddr_in serverSa;
    int rc;

    memset(&serverSa, 0, sizeof(serverSa));
    serverSa.sin_family = AF_INET;
    serverSa.sin_addr.s_addr = htonl(INADDR_ANY);
    if (parsing->port == -1)
        exit(84);
    serverSa.sin_port = htons(parsing->port);
    rc = bind(s, (struct sockaddr *)&serverSa, sizeof(serverSa));
    if (rc < 0) {
        free_server(parsing);
        return -1;
    }
    return 0;
}

int start_listening(int s)
{
    int rc = listen(s, MAX_CLIENTS);

    if (rc < 0) {
        return -1;
    }
    return 0;
}
