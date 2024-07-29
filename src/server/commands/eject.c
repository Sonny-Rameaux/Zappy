/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** eject
*/

#include "commands.h"

static bool check_eject(char **args)
{
    return size_arr(args) == 0;
}

static void get_eject_xy(
    enum Orientation dest_orient,
    enum Orientation *src_orient,
    pos_xy_t *dest_pos
)
{
    switch (dest_orient) {
        case N:
            dest_pos->y --;
            *src_orient = S;
            break;
        case S:
            dest_pos->y ++;
            *src_orient = N;
            break;
        case W:
            dest_pos->x --;
            *src_orient = E;
            break;
        case E:
            dest_pos->x ++;
            *src_orient = W;
            break;
        default:
            break;
    }
}

static void eject_player(
    client_info_t *player,
    pos_xy_t dest_pos,
    enum Orientation src_orient,
    log_t *server
)
{
    player->pos_x = (dest_pos.x) % server->gui_map->width;
    player->pos_y = (dest_pos.y) % server->gui_map->height;
    dprintf(
        player->sd,
        "eject: %s\r\n",
        orientation_to_str(src_orient)
    );
}

static void edi_event(int graph, egg_t *egg)
{
    if (graph) {
        dprintf(
            graph,
            "edi %d\r\n",
            egg->id
        );
    }
}

static bool delete_eggs_on_tile_bis(
    log_t *server,
    int i,
    int x,
    int y
)
{
    int index = 0;

    for (egg_t *tmp = server->parsed->teams[i]->eggs; tmp; tmp = tmp->next) {
        if (tmp->x == x && tmp->y == y) {
            edi_event(
                server->graphic_connected,
                get_egg_at_index(server->parsed->teams[i]->eggs, index)
            );
            delete_egg(&server->parsed->teams[i]->eggs, index);
            return true;
        }
        index ++;
    }
    return false;
}

static void delete_eggs_on_tile(log_t *server, int x, int y)
{
    for (int i = 0; server->parsed->teams[i] != NULL; i ++) {
        if (delete_eggs_on_tile_bis(server, i, x, y))
            continue;
    }
}

void event_eject_player(log_t *server, size_t i,
    pos_xy_t dest_pos, enum Orientation src_orient)
{
    eject_player(&server->clients[i], dest_pos, src_orient, server);
    dprintf(server->graphic_connected,
        "pex %d\r\n", server->clients[i].sd);
}

void eject_command(log_t *server, client_info_t *client, char **args)
{
    pos_xy_t dest_pos = {.x = client->pos_x, .y = client->pos_y};
    enum Orientation src_orient;

    if (!check_eject(args)) {
        KO_OUTPUT(client->sd);
        return;
    }
    get_eject_xy(client->orient, &src_orient, &dest_pos);
    for (size_t i = 0; i < MAX_CLIENTS; i ++) {
        if (server->clients[i].sd <= 0 || server->clients[i].sd == client->sd)
            continue;
        if (server->clients[i].pos_x == client->pos_x &&
            server->clients[i].pos_y == client->pos_y) {
            event_eject_player(server, i, dest_pos, src_orient);
        }
    }
    delete_eggs_on_tile(server, client->pos_x, client->pos_y);
    delete_eggs_on_tile(server, dest_pos.x, dest_pos.y);
    OK_OUTPUT(client->sd);
    client->command_delay = 7.0 / server->parsed->freq;
}
