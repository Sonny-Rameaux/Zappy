/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** quit
*/
#include "server.h"

void quit_command(log_t *logins, client_info_t *client, char **args)
{
    (void)args;
    close(client->sd);
    client->sd = 0;
    client->logged_in = 0;
    if (client->cmd_queue)
        free_list(client->cmd_queue);
    if (client->inventory) {
        if (client->inventory->items)
            free_items(client->inventory->items);
        free(client->inventory);
    }
    free(client->team_name);
    client->level = 1;
    if (client->is_graphic)
        logins->graphic_connected = 0;
    client->is_graphic = 0;
    client->command_delay = 0.0;
    client->team_name = NULL;
    client->inventory = NULL;
    client->cmd_queue = NULL;
}
