/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** broadcast
*/

#include "commands.h"

/*
    return 1; // Front
    return 2; // Front-left
    return 3; // Left
    return 4; // Back-left
    return 5; // Back
    return 6; // Back-right
    return 7; // Right
    return 8; // Front-right
*/

void calc_shortest_path(client_info_t *receiver, client_info_t *sender,
    pos_xy_t *pos, map_t *map)
{
    int x1 = receiver->pos_x - sender->pos_x;
    int x2 = (receiver->pos_x - map->width) - sender->pos_x;
    int y1 = receiver->pos_y - sender->pos_y;
    int y2 = (receiver->pos_y - map->height) - sender->pos_y;

    pos->x = (abs(x1) > abs(x2) ? x2 : x1);
    pos->y = (abs(y1) > abs(y2) ? y2 : y1);
}

static int chose_orient(double angle)
{
    if (angle >= 337.5 || angle < 22.5)
        return 7;
    if (angle >= 22.5 && angle < 67.5)
        return 8;
    if (angle >= 67.5 && angle < 112.5)
        return 1;
    if (angle >= 112.5 && angle < 157.5)
        return 2;
    if (angle >= 157.5 && angle < 202.5)
        return 3;
    if (angle >= 202.5 && angle < 247.5)
        return 4;
    if (angle >= 247.5 && angle < 292.5)
        return 5;
    if (angle >= 292.5 && angle < 337.5)
        return 6;
    return 0;
}

static void change_orient(client_info_t *sender, int *orientation)
{
    if (sender->orient == N)
        *orientation = *orientation;
    if (sender->orient == E)
        *orientation = (*orientation + 2) % 8;
    if (sender->orient == S)
        *orientation = (*orientation + 4) % 8;
    if (sender->orient == W)
        *orientation = (*orientation + 6) % 8;
}

int get_dir(client_info_t *receiver, client_info_t *sender, map_t *map)
{
    double angle;
    int orientation = 0;
    pos_xy_t pos;

    if (sender->pos_x == receiver->pos_x && sender->pos_y == receiver->pos_y)
        return (0);
    calc_shortest_path(sender, receiver, &pos, map);
    angle = atan2(-pos.y, pos.x) * 180 / M_PI;
    if (angle < 0)
        angle += 360;
    orientation = chose_orient(angle);
    change_orient(receiver, &orientation);
    if (orientation == 0)
        orientation = 8;
    return (orientation);
}

static void choose_letter(char ch, char *encrypted, int shift, int i)
{
    if (ch >= 'a' && ch <= 'z') {
        encrypted[i] = ((ch - 'a' + shift) % 26) + 'a';
    } else if (ch >= 'A' && ch <= 'Z') {
        encrypted[i] = ((ch - 'A' + shift) % 26) + 'A';
    } else {
        encrypted[i] = ch;
    }
}

char *caesar_cipher(char *message, int shift)
{
    int length = my_strlen(message);
    char *encrypted = malloc(length + 1);
    char ch;

    if (encrypted == NULL) {
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        ch = message[i];
        choose_letter(ch, encrypted, shift, i);
    }
    encrypted[length] = '\0';
    return encrypted;
}

static void send_broadcast(client_info_t *sdr, client_info_t *rcvr,
    log_t *server, char *message)
{
    int direction;
    char *encrypted_message;

    direction = get_dir(rcvr, sdr, server->gui_map);
    encrypted_message = caesar_cipher(message, direction);
    dprintf(rcvr->sd, "message %d,%s\r\n", direction, encrypted_message);
    free(encrypted_message);
}

static int broadcasting_same_tile(client_info_t *rvr,
    client_info_t *sdr, char *message)
{
    if (rvr->pos_x == sdr->pos_x && rvr->pos_y == sdr->pos_y && sdr != rvr) {
        dprintf(rvr->sd, "message 0,%s\r\n", message);
        return 1;
    }
    return 0;
}

void broadcast_command(log_t *server, client_info_t *sdr, char **args)
{
    client_info_t *rvr;
    char *message;

    if (args[0] == NULL) {
        dprintf(sdr->sd, "ko\r\n");
        return;
    }
    message = count_str(args);
    if (server->graphic_connected)
        dprintf(server->graphic_connected, "pbc %d %s\r\n", sdr->sd, message);
    for (int i = 0; i < server->client_nbs; i++) {
        rvr = &server->clients[i];
        if (broadcasting_same_tile(rvr, sdr, message))
            continue;
        if (rvr == sdr || !rvr->logged_in || rvr->is_graphic)
            continue;
        send_broadcast(sdr, rvr, server, message);
    }
    dprintf(sdr->sd, "ok\r\n"), free(message);
}
