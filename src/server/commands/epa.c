/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** epa
*/

#include "commands.h"

static bool check_epa(char **args)
{
    return size_arr(args) == 0;
}

static void send_epa(log_t *server, egg_t *tmp, client_info_t *client)
{
    if (server->graphic_connected) {
        dprintf(
            server->graphic_connected,
            "enw %d %d %d %d\r\n",
            tmp->id,
            client->sd,
            tmp->x,
            tmp->y
        );
    }
}

void epa_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_epa(args)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    for (int i = 0; server->parsed->teams[i] != NULL; i ++) {
        for (egg_t *tmp = server->parsed->teams[i]->eggs;
            tmp; tmp = tmp->next) {
            send_epa(server, tmp, client);
        }
    }
}
