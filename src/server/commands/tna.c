/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** tna
*/

#include "commands.h"

static bool check_tna(char **args)
{
    return size_arr(args) == 0;
}

void tna_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_tna(args)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    for (int i = 0; server->parsed->teams[i] != NULL; i++) {
        dprintf(
            client->sd,
            "tna %s\r\n",
            server->parsed->teams[i]->name
        );
    }
}
