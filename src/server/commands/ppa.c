/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** ppa
*/

#include "commands.h"

static bool check_ppa(char **args)
{
    return size_arr(args) == 0;
}

void ppa_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_ppa(args)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    for (int i = 0; i < MAX_CLIENTS; i ++) {
        if (server->clients[i].logged_in && !server->clients[i].is_graphic) {
            PPO_OUTPUT(
                client->sd,
                server->clients[i].sd,
                server->clients[i].pos_x,
                server->clients[i].pos_y,
                orientation_to_str(server->clients[i].orient)
            );
        }
    }
}
