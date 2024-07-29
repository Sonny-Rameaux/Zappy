/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** loop_look
*/
#include "commands.h"

static char *inventory_to_string(inv_t *inventory)
{
    char *result = malloc(1024);
    char *item_str;
    item_t *item;

    result[0] = '\0';
    if (inventory == NULL || inventory->items == NULL) {
        strcpy(result, "");
        return result;
    }
    item = inventory->items;
    while (item != NULL) {
        item_str = malloc(sizeof(char) * 256);
        snprintf(item_str, 256, "%s_%d", item->name, item->quantity);
        strcat(result, item_str);
        if (item->next != NULL)
            strcat(result, " ");
        item = item->next;
        free(item_str);
    }
    return result;
}

static void fill_tile(map_t *map, pos_xy_t *pos, char *buffer, size_t *offset)
{
    char *inv_str;
    tile_t *tile = get_tile(map, pos->x, pos->y);
    int written;

    if (tile != NULL) {
        inv_str = inventory_to_string(tile->inventory);
        written = snprintf(buffer + *offset, 1000, "%s", inv_str);
        *offset += written;
        free(inv_str);
    }
}

void loop_down(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info)
{
    pos_xy_t pos;

    for (int j = i; j > -i - 1; j--) {
        pos.x = ((c->pos_x + j) % map->width + map->width) % map->width;
        pos.y = ((c->pos_y + i) % map->height + map->height) % map->height;
        fill_tile(map, &pos, buf_info->buff, buf_info->offset);
        if (!(i == c->level && j == -i)) {
            snprintf(buf_info->buff + *buf_info->offset, 2, ",");
            (*buf_info->offset)++;
        }
    }
}

void loop_up(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info)
{
    pos_xy_t pos;

    for (int j = -i; j < i + 1; j++) {
        pos.x = ((c->pos_x + j) % map->width + map->width) % map->width;
        pos.y = ((c->pos_y - i) % map->height + map->height) % map->height;
        fill_tile(map, &pos, buf_info->buff, buf_info->offset);
        if (!(i == c->level && j == i)) {
            snprintf(buf_info->buff + *buf_info->offset, 2, ",");
            (*buf_info->offset)++;
        }
    }
}

void loop_right(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info)
{
    pos_xy_t pos;

    for (int j = -i; j < i + 1; j++) {
        pos.x = ((c->pos_x + i) % map->width + map->width) % map->width;
        pos.y = ((c->pos_y + j) % map->height + map->height) % map->height;
        fill_tile(map, &pos, buf_info->buff, buf_info->offset);
        if (!(i == c->level && j == i)) {
            snprintf(buf_info->buff + *buf_info->offset, 2, ",");
            (*buf_info->offset)++;
        }
    }
}

void loop_left(int i, client_info_t *c, map_t *map, buffer_info_t *buf_info)
{
    pos_xy_t pos;

    for (int j = i; j > -i - 1; j--) {
        pos.x = ((c->pos_x - i) % map->width + map->width) % map->width;
        pos.y = ((c->pos_y + j) % map->height + map->height) % map->height;
        fill_tile(map, &pos, buf_info->buff, buf_info->offset);
        if (!(i == c->level && j == -i)) {
            snprintf(buf_info->buff + *(buf_info->offset), 2, ",");
            (*(buf_info->offset))++;
        }
    }
}
