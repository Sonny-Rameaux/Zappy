/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** look
*/
#include "commands.h"

static void look_down(map_t *map, client_info_t *c, buffer_info_t *buf_info)
{
    for (int i = 0; i < c->level + 1; i++) {
        loop_down(i, c, map, buf_info);
    }
}

static void look_up(map_t *map, client_info_t *c, buffer_info_t *buf_info)
{
    for (int i = 0; i < c->level + 1; i++) {
        loop_up(i, c, map, buf_info);
    }
}

static void look_right(map_t *map, client_info_t *c, buffer_info_t *buf_info)
{
    for (int i = 0; i < c->level + 1; i++) {
        loop_right(i, c, map, buf_info);
    }
}

static void look_left(map_t *map, client_info_t *c, buffer_info_t *buf_info)
{
    for (int i = 0; i < c->level + 1; i++) {
        loop_left(i, c, map, buf_info);
    }
}

void choose_orient(map_t *map, client_info_t *client, buffer_info_t *buf_info)
{
    switch (client->orient) {
        case S:
            look_down(map, client, buf_info);
            break;
        case N:
            look_up(map, client, buf_info);
            break;
        case E:
            look_right(map, client, buf_info);
            break;
        case W:
            look_left(map, client, buf_info);
            break;
    }
}

static void assign_players_on_map(client_info_t *clients, map_t *map)
{
    for (int i = 0; i < MAX_CLIENTS; i ++) {
        if (clients[i].logged_in && !clients[i].is_graphic) {
            add_item_to_map(
                map,
                (pos_xy_t){
                    clients[i].pos_x,
                    clients[i].pos_y
                },
                "player",
                1
            );
        }
    }
}

static void assign_eggs_on_map(team_t **teams, map_t *map)
{
    for (int i = 0; teams[i]; i ++) {
        for (egg_t *tmp = teams[i]->eggs; tmp; tmp = tmp->next) {
            add_item_to_map(
                map,
                (pos_xy_t){
                    tmp->x,
                    tmp->y
                },
                "egg",
                1
            );
        }
    }
}

void look(log_t *server, client_info_t *client, char **args)
{
    char buffer[44444];
    size_t offset = 0;
    buffer_info_t buf_info;
    map_t *map_copy = copy_map(server->gui_map);

    (void)args;
    assign_players_on_map(server->clients, map_copy);
    assign_eggs_on_map(server->parsed->teams, map_copy);
    buf_info.buff = buffer;
    buf_info.offset = &offset;
    snprintf(buffer, 2, "[");
    offset++;
    choose_orient(map_copy, client, &buf_info);
    snprintf(buffer + offset, 2, "]");
    offset++;
    dprintf(client->sd, "%s\r\n", buffer);
    client->command_delay = 7.0 / server->parsed->freq;
    free_map(map_copy);
}
