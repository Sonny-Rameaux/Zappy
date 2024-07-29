/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** debug
*/
#include "commands.h"

void debug_command(log_t *server, client_info_t *client, char **args)
{
    (void)args;
    (void)server;
    dprintf(client->sd, "(%d, %d)\n", client->pos_x, client->pos_y);
    switch (client->orient) {
        case N:
            dprintf(client->sd, "Facing North");
            break;
        case S:
            dprintf(client->sd, "Facing South");
            break;
        case E:
            dprintf(client->sd, "Facing East");
            break;
        case W:
            dprintf(client->sd, "Facing West");
            break;
    }
    dprintf(client->sd, "\r\n");
}
