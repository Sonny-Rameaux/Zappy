/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** msz
*/

#include "commands.h"

static bool check_msz(char **args)
{
    return size_arr(args) == 0;
}

void msz_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_msz(args)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    MSZ_OUTPUT(
        client->sd,
        server->gui_map->width,
        server->gui_map->height
    );
}
