/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** fill_map
*/
#include "server.h"

const char *resources[] = {
    "food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"
};

/*
AT LEAST ONE OF EACH : width * height * density

- food : 0.5
- linemate : 0.3
- deraumere : 0.15
- sibur : 0.1
- mendiane : 0.1
- phiras : 0.08
- thystame : 0.05
*/

double densities[] = {
    0.5, 0.3, 0.15, 0.1,
    0.1, 0.08, 0.05
};

void fill_map_with_resources(map_t *map)
{
    int total_cells = map->width * map->height;
    int resource_counts[7];
    int x;
    int y;

    srand(time(NULL));
    for (int i = 0; i < 7; i++) {
        resource_counts[i] = (int)(total_cells * densities[i]);
        if (resource_counts[i] == 0) {
            resource_counts[i] = 1;
        }
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < resource_counts[i]; j++) {
            x = rand() % map->width;
            y = rand() % map->height;
            add_item_to_map(map, (pos_xy_t){x, y}, resources[i], 1);
        }
    }
}
