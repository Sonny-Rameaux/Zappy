/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** fork
*/

#include "commands.h"

static bool check_fork(char **args)
{
    return size_arr(args) == 0;
}

static void pfk_event(log_t *server, client_info_t *client)
{
    if (server->graphic_connected) {
        dprintf(
            server->graphic_connected,
            "pfk %d\r\n",
            client->sd
        );
    }
}

static void enw_event(log_t *server, egg_t *egg, client_info_t *client)
{
    if (server->graphic_connected) {
        dprintf(
            server->graphic_connected,
            "enw %d %d %d %d\r\n",
            egg->id,
            client->sd,
            egg->x,
            egg->y
        );
    }
}

static void add_fork_egg(log_t *server, client_info_t *client)
{
    for (int i = 0; server->parsed->teams[i] != NULL; i ++) {
        if (strcmp(server->parsed->teams[i]->name, client->team_name) == 0) {
            add_egg(
                &server->parsed->teams[i]->eggs,
                server->parsed->egg_n,
                client->pos_x,
                client->pos_y
            );
            server->parsed->egg_n ++;
            enw_event(server, server->parsed->teams[i]->eggs, client);
            break;
        }
    }
}

void fork_command(log_t *server, client_info_t *client, char **args)
{
    pfk_event(server, client);
    if (!check_fork(args)) {
        KO_OUTPUT(client->sd);
        return;
    }
    for (size_t i = 0; server->parsed->teams[i] != NULL; i ++) {
        if (strcmp(server->parsed->teams[i]->name, client->team_name) == 0) {
            add_fork_egg(server, client);
            client->command_delay = 42.0 / server->parsed->freq;
            OK_OUTPUT(client->sd);
            return;
        }
    }
    KO_OUTPUT(client->sd);
}
