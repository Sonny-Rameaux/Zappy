/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** copy_map
*/
#include "server.h"

item_t *copy_items(item_t *original)
{
    item_t *copy;

    if (original == NULL) {
        return NULL;
    }
    copy = malloc(sizeof(item_t));
    if (copy == NULL) {
        return NULL;
    }
    copy->name = strdup(original->name);
    copy->quantity = original->quantity;
    copy->next = copy_items(original->next);
    return copy;
}

inv_t *copy_inventory(inv_t *original)
{
    inv_t *copy = malloc(sizeof(inv_t));

    if (copy == NULL) {
        return NULL;
    }
    copy->items = copy_items(original->items);
    return copy;
}

int copy_tiles(map_t *original, map_t *copy, int i)
{
    copy->tiles[i] = malloc(sizeof(tile_t) * original->width);
    if (copy->tiles[i] == NULL) {
        for (int j = 0; j < i; j++)
            free(copy->tiles[j]);
        free(copy->tiles), free(copy);
        return 0;
    }
    for (int j = 0; j < original->width; j++) {
        copy->tiles[i][j].inventory =
            copy_inventory(original->tiles[i][j].inventory);
    }
    return 1;
}

map_t *copy_map(map_t *original)
{
    map_t *copy = malloc(sizeof(map_t));

    if (copy == NULL)
        return NULL;
    copy->width = original->width;
    copy->height = original->height;
    copy->tiles = malloc(sizeof(tile_t *) * original->height);
    if (copy->tiles == NULL) {
        free(copy);
        return NULL;
    }
    for (int i = 0; i < original->height; i++) {
        if (copy_tiles(original, copy, i) == 0)
            return NULL;
    }
    return copy;
}
