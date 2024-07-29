/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** bct
*/

#include "commands.h"

static bool check_bct(char **args, int *x, int *y)
{
    if (size_arr(args) != 2) {
        return false;
    }
    trim_newline(args[1]);
    if (!is_num(args[0]) || !is_num(args[1])) {
        return false;
    }
    *x = atoi(args[0]);
    *y = atoi(args[1]);
    return true;
}

void send_bct_msg(int sd, int x, int y, map_t *map)
{
    char buffer[UPPER] = "";

    snprintf(buffer, UPPER, "bct %d %d ", x, y);
    display_items(
        map->tiles[y][x].inventory->items,
        base_item_displayer,
        buffer + strlen(buffer)
    );
    dprintf(sd, "%s\r\n", buffer);
}

void bct_command(log_t *server, client_info_t *client, char **args)
{
    int x = 0;
    int y = 0;

    if (!check_bct(args, &x, &y)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    send_bct_msg(client->sd, x, y, server->gui_map);
}
