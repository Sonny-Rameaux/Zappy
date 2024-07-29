/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** mct
*/

#include "commands.h"

static bool check_mct(char **args)
{
    return size_arr(args) == 0;
}

void mct_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_mct(args)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    for (int x = 0; x < server->gui_map->width; x++) {
        for (int y = 0; y < server->gui_map->height; y++) {
            send_bct_msg(
                client->sd,
                x,
                y,
                server->gui_map
            );
        }
    }
}
