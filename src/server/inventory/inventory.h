/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** inventory
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_
    #define MAX_STR_LEN 44444

    #include "../server.h"

/* INVENTORY */
typedef struct item_s {
    char *name;
    int quantity;
    struct item_s *next;
} item_t;

typedef struct inv_s {
    struct item_s *items;
} inv_t;

typedef struct {
    int x;
    int y;
} pos_xy_t;

/* handle_items.c */
void free_items(item_t *items);
void add_item_to_inventory(
    inv_t *inventory,
    const char *item_name,
    int quantity
);
void add_item_to_map(
    map_t *map,
    pos_xy_t pos,
    const char *item,
    int quantity
);
int is_item_in_inventory(inv_t *inv, char *name);
item_t *find_item_in_inventory(inv_t *inv, char *name);

/* utils.c */
void display_items(
    item_t *head,
    void displayer(item_t *, char *),
    char *buffer
);
void base_item_displayer(item_t *item, char *buffer);

// void display_items(
//     item_t *head,
//     void displayer(item_t *, int),
//     int fd
// );
// void base_item_displayer(item_t *item, int fd);

#endif /* !INVENTORY_H_ */
