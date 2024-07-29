/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** pin
*/

#include "commands.h"

static bool check_pin(char **args, int *n, int *in, log_t *server)
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

static void send_pin_msg(int sd, client_info_t client)
{
    char buffer[UPPER] = "";

    snprintf(
        buffer,
        UPPER,
        "pin %d %d %d ",
        client.sd,
        client.pos_x,
        client.pos_y
    );
    display_items(
        client.inventory->items,
        base_item_displayer,
        buffer + strlen(buffer)
    );
    dprintf(sd, "%s\r\n", buffer);
}

void pin_command(log_t *server, client_info_t *client, char **args)
{
    int n;
    int in;

    if (!check_pin(args, &n, &in, server)) {
        SBP_OUTPUT(client->sd);
        return;
    }
    send_pin_msg(
        client->sd,
        server->clients[in]
    );
}
