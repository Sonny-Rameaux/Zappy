/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** utils
*/

#include "inventory.h"

void display_items(
    item_t *head,
    void displayer(item_t *, char *),
    char *buffer
)
{
    item_t *tmp = head;

    if (!tmp) {
        displayer(tmp, buffer);
    }
    while (tmp) {
        displayer(tmp, buffer);
        tmp = tmp->next;
    }
}

void base_item_displayer(item_t *item, char *buffer)
{
    if (!item) {
        snprintf(buffer + strlen(buffer), MAX_STR_LEN - strlen(buffer), "\n");
        return;
    }
    if (item->next) {
        snprintf(buffer + strlen(buffer), MAX_STR_LEN - strlen(buffer),
            "%s_%d, ", item->name, item->quantity);
        return;
    }
    snprintf(buffer + strlen(buffer), MAX_STR_LEN - strlen(buffer),
        "%s_%d\n", item->name, item->quantity);
}

// void display_items(
//     item_t *head,
//     void displayer(item_t *, int),
//     int fd
// )
// {
//     item_t *tmp = head;

//     if (!tmp) {
//         displayer(tmp, fd);
//     }
//     while (tmp) {
//         displayer(tmp, fd);
//         tmp = tmp->next;
//     }
// }

// void base_item_displayer(item_t *item, int fd)
// {
//     if (!item) {
//         return;
//     }
//     dprintf(
//         fd,
//         "%s_%d",
//         item->name,
//         item->quantity
//     );
//     if (item->next) {
//         dprintf(fd, ", ");
//         return;
//     }
// }
