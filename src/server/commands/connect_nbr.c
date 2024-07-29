/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** connect_nbr
*/

#include "commands.h"

static bool check_connect_nbr(char **args)
{
    return size_arr(args) == 0;
}

void connect_nbr_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_connect_nbr(args)) {
        KO_OUTPUT(client->sd);
        return;
    }
    for (size_t i = 0; server->parsed->teams[i] != NULL; i ++) {
        if (strcmp(server->parsed->teams[i]->name, client->team_name) == 0) {
            dprintf(
                client->sd,
                "%d\r\n",
                eggs_len(server->parsed->teams[i]->eggs)
            );
            return;
        }
    }
    KO_OUTPUT(client->sd);
}
