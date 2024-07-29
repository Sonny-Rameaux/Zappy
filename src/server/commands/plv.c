/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** plv
*/

#include "commands.h"

static bool check_plv(char **args, int *n, int *in, log_t *server)
{
    if (size_arr(args) != 1)
        return false;
    trim_newline(args[0]);
    if (!is_num(args[0]))
        return false;
    *n = atoi(args[0]);
    for (size_t i = 0; i < MAX_CLIENTS; i ++) {
        if (server->clients[i].sd == *n) {
            *in = i;
            return true;
        }
    }
    return false;
}

void plv_command(log_t *server, client_info_t *client, char **args)
{
    int n;
    int in;

    if (!check_plv(args, &n, &in, server)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    PLV_OUTPUT(
        client->sd,
        n,
        server->clients[in].level
    );
}
