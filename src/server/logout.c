/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** logout
*/
#include "server.h"

void logout_cmd(log_t *logins, client_info_t *cli, char **args)
{
    (void)args;
    close(cli->sd);
    cli->sd = 0;
    cli->logged_in = 0;
    if (cli->team_name)
        free(cli->team_name);
    free_list(cli->cmd_queue);
    if (cli->inventory) {
        if (cli->inventory->items)
            free_items(cli->inventory->items);
        free(cli->inventory);
    }
    cli->level = 1;
    cli->command_delay = 0.0;
    if (cli->is_graphic)
        logins->graphic_connected = 0;
    cli->is_graphic = 0;
    cli->team_name = NULL;
    cli->inventory = NULL;
    cli->cmd_queue = NULL;
}
