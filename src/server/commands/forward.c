/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** forward
*/

#include "commands.h"

static bool check_forward(char **args)
{
    return size_arr(args) == 0;
}

static void forward_update_xy(enum Orientation orient, int *x, int *y)
{
    switch (orient) {
        case N:
            (*y) --;
            break;
        case E:
            (*x) ++;
            break;
        case S:
            (*y) ++;
            break;
        case W:
            (*x) --;
            break;
    }
}

static void offset_correction(int *x, int *y, int w, int h)
{
    if ((*x) >= w)
        (*x) = 0;
    if ((*x) < 0)
        (*x) = w - 1;
    if ((*y) >= h)
        (*y) = 0;
    if ((*y) < 0)
        (*y) = h - 1;
}

void forward_command(log_t *server, client_info_t *client, char **args)
{
    int x = 0;
    int y = 0;

    if (!check_forward(args)) {
        KO_OUTPUT(client->sd);
        return;
    }
    forward_update_xy(client->orient, &x, &y);
    client->pos_x = client->pos_x + x;
    client->pos_y = client->pos_y + y;
    offset_correction(
        &client->pos_x,
        &client->pos_y,
        server->parsed->width,
        server->parsed->height
    );
    client->command_delay = 7.0 / server->parsed->freq;
    OK_OUTPUT(client->sd);
}
