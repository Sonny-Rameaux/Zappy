/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** take_obj
*/

#include "commands.h"

static bool check_take(char **args)
{
    if (!args || size_arr(args) != 1)
        return false;
    trim_newline(args[0]);
    return true;
}

static void pgt_event(int graph, int client, char *item)
{
    if (graph) {
        dprintf(
            graph,
            "pgt %d %s\r\n",
            client,
            item
        );
    }
}

bool bad_tile_ts(int x, int y, log_t *server)
{
    if (x < 0)
        return true;
    if (y < 0)
        return true;
    if (x >= server->gui_map->width)
        return true;
    if (y >= server->gui_map->height)
        return true;
    return false;
}

void take_command(log_t *server, client_info_t *client, char **args)
{
    int x = client->pos_x;
    int y = client->pos_y;

    if (!check_take(args) || bad_tile_ts(x, y, server)) {
        KO_OUTPUT(client->sd);
        return;
    }
    if (!is_item_in_inventory(
        server->gui_map->tiles[y][x].inventory, args[0])) {
        KO_OUTPUT(client->sd);
        return;
    }
    add_item_to_inventory(client->inventory, args[0], 1);
    add_item_to_inventory(server->gui_map->tiles[y][x].inventory, args[0], -1);
    client->command_delay = 7.0 / server->parsed->freq;
    OK_OUTPUT(client->sd);
    pgt_event(server->graphic_connected, client->sd, args[0]);
}
