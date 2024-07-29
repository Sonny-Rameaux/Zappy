/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** sgt
*/

#include "commands.h"

static bool check_sgt(char **args)
{
    return size_arr(args) == 0;
}

void sgt_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_sgt(args))
        return;
    SGT_OUTPUT(
        client->sd,
        server->parsed->freq
    );
}
