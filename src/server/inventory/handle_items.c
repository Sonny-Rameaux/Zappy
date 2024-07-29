/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** handle_items
*/

#include "inventory.h"

void free_items(item_t *head)
{
    item_t *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->name);
        free(tmp);
    }
}

item_t *find_item_in_inventory(inv_t *inv, char *name)
{
    for (item_t *tmp = inv->items; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, name) == 0) {
            return tmp;
        }
    }
    return NULL;
}

int is_item_in_inventory(inv_t *inv, char *name)
{
    if (!inv || !inv->items)
        return 0;
    for (item_t *tmp = inv->items; tmp; tmp = tmp->next) {
        if (strcmp(tmp->name, name) == 0)
            return tmp->quantity;
    }
    return 0;
}

static void add_item_to_list(
    item_t **head,
    const char *item_name,
    int quantity
)
{
    item_t *item = malloc(sizeof(item_t));

    item->name = strdup(item_name);
    item->quantity = quantity;
    if (!*head) {
        item->next = NULL;
        *head = item;
        return;
    }
    item->next = *head;
    *head = item;
}

static void delete_item_from_list(item_t **head, const char *item_name)
{
    item_t *dest = NULL;
    item_t *tmp = *head;

    while (tmp) {
        if (strcmp(tmp->name, item_name) == 0) {
            tmp = tmp->next;
            continue;
        }
        add_item_to_list(&dest, tmp->name, tmp->quantity);
        tmp = tmp->next;
    }
    free_items(*head);
    *head = dest;
}

void add_item_to_inventory(
    inv_t *inventory,
    const char *item_name,
    int quantity
)
{
    item_t *tmp = inventory->items;
    bool set = false;

    while (tmp) {
        if (strcmp(tmp->name, item_name) == 0) {
            tmp->quantity += quantity;
            set = true;
            break;
        }
        tmp = tmp->next;
    }
    if (set) {
        if (tmp->quantity <= 0)
            delete_item_from_list(&inventory->items, item_name);
        return;
    }
    if (quantity <= 0)
        return;
    add_item_to_list(&inventory->items, item_name, quantity);
}

void add_item_to_map(
    map_t *map,
    pos_xy_t pos,
    const char *item,
    int quantity
)
{
    int x = pos.x;
    int y = pos.y;

    if (x >= 0 && x < map->width && y >= 0 && y < map->height) {
        add_item_to_inventory(map->tiles[y][x].inventory, item, quantity);
        return;
    }
    fprintf(stderr, "Error: Tile position (%d, %d) out of bounds\n", x, y);
}
