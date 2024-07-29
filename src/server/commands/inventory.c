/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** inventory
*/

#include "commands.h"

static bool check_inventory(char **args)
{
    return size_arr(args) == 0;
}

void inventory_command(log_t *server, client_info_t *client, char **args)
{
    char buffer[44444];
    int offset = 0;

    if (!check_inventory(args)) {
        KO_OUTPUT(client->sd);
        return;
    }
    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "[");
    for (item_t *tmp = client->inventory->items; tmp; tmp = tmp->next) {
        offset += snprintf(buffer + offset, sizeof(buffer) - offset, "%s %d",
            tmp->name, tmp->quantity);
        if (tmp->next)
            offset += snprintf(buffer + offset, sizeof(buffer) - offset, ", ");
    }
    offset += snprintf(buffer + offset, sizeof(buffer) - offset, "]\r\n");
    dprintf(client->sd, "%s", buffer);
    client->command_delay = 1.0 / server->parsed->freq;
}
