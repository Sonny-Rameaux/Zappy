/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** map
*/
#include "server.h"

map_t *create_map(int width, int height)
{
    map_t *map = malloc(sizeof(map_t));

    map->width = width;
    map->height = height;
    map->tiles = malloc(height * sizeof(tile_t *));
    for (int i = 0; i < height; ++i) {
        map->tiles[i] = malloc(width * sizeof(tile_t));
        for (int j = 0; j < width; ++j) {
            map->tiles[i][j].inventory = malloc(sizeof(inv_t));
            map->tiles[i][j].inventory->items = NULL;
        }
    }
    return map;
}

void free_map(map_t *map)
{
    for (int i = 0; i < map->height; ++i) {
        for (int j = 0; j < map->width; ++j) {
            free_items(map->tiles[i][j].inventory->items);
            free(map->tiles[i][j].inventory);
        }
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map);
}

void shift_items(char *start_pos, size_t shift_length)
{
    memmove(start_pos, start_pos + shift_length,
        strlen(start_pos + shift_length) + 1);
}

tile_t *get_tile(map_t *map, int x, int y)
{
    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        return &(map->tiles[y][x]);
    } else {
        fprintf(stderr, "Error: Tile position (%d, %d) out of bounds\n", x, y);
        return NULL;
    }
}
