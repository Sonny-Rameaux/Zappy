/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** sst
*/

#include "commands.h"

static bool check_sst(char **args, int *f)
{
    if (size_arr(args) != 1)
        return false;
    trim_newline(args[0]);
    if (!is_num(args[0]))
        return false;
    *f = atoi(args[0]);
    return true;
}

void sst_command(log_t *server, client_info_t *client, char **args)
{
    int f;

    if (!check_sst(args, &f))
        return;
    server->parsed->freq = f;
    SST_OUTPUT(
        client->sd,
        f
    );
}
