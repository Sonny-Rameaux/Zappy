/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** turn
*/
#include "commands.h"

void right_command(log_t *server, client_info_t *client, char **args)
{
    (void)server;
    (void)args;
    switch (client->orient) {
        case N:
            client->orient = E;
            break;
        case E:
            client->orient = S;
            break;
        case S:
            client->orient = W;
            break;
        case W:
            client->orient = N;
            break;
    }
    OK_OUTPUT(client->sd);
}

void left_command(log_t *server, client_info_t *client, char **args)
{
    (void)server;
    (void)args;
    switch (client->orient) {
        case N:
            client->orient = W;
            break;
        case W:
            client->orient = S;
            break;
        case S:
            client->orient = E;
            break;
        case E:
            client->orient = N;
            break;
    }
    OK_OUTPUT(client->sd);
}
