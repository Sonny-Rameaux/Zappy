/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** assign_team
*/
#include "server.h"

static int assign_graphic(log_t *server, int i, int is_graphic)
{
    if (!server->graphic_connected && is_graphic == 0) {
        server->clients[i].is_graphic = 1;
        server->graphic_connected = server->clients[i].sd;
        return 1;
    }
    if (server->graphic_connected && is_graphic == 0) {
        dprintf(server->clients[i].sd, "There can be only one GRAPHIC!\r\n");
        return -1;
    }
    return 0;
}

static void ebo_event(int graph, egg_t *egg)
{
    if (graph) {
        dprintf(
            graph,
            "ebo %d\r\n",
            egg->id
        );
    }
}

static void event_new_player(log_t *server, int teams, int i)
{
    ebo_event(server->graphic_connected, server->parsed->teams[teams]->eggs);
    assign_egg_position_to_player(
        &server->parsed->teams[teams]->eggs,
        &server->clients[i]
    );
    if (server->graphic_connected) {
        dprintf(
            server->graphic_connected,
            "pnw %d %d %d %s %d %s\r\n",
            server->clients[i].sd,
            server->clients[i].pos_x,
            server->clients[i].pos_y,
            orientation_to_str(server->clients[i].orient),
            1,
            server->clients[i].team_name
        );
    }
}

static int assign_team_args(log_t *server, char *command, int teams, int i)
{
    int is_graphic = strcmp(command, "GRAPHIC");

    if ((strcmp(server->parsed->teams[teams]->name, command) == 0
        && server->parsed->teams[teams]->eggs) || is_graphic == 0) {
        if (assign_graphic(server, i, is_graphic) == -1)
            return -1;
        server->clients[i].team_name = strdup(command);
        server->clients[i].logged_in = 1;
        dprintf(server->clients[i].sd, "%d %d\r\n",
            server->parsed->width, server->parsed->height);
        if (!server->clients[i].is_graphic) {
            event_new_player(server, teams, i);
        }
        return 1;
    }
    return 0;
}

void assign_team(char *command, log_t *server, int i)
{
    int is_correct;

    trim_newline(command);
    for (int teams = 0; server->parsed->teams[teams]; teams++) {
        is_correct = assign_team_args(server, command, teams, i);
        if (is_correct == 1 || is_correct == -1)
            break;
    }
    if (server->clients[i].team_name == NULL)
        dprintf(server->clients[i].sd, "ko\r\n");
}
