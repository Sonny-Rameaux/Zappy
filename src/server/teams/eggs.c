/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** eggs
*/

#include "teams.h"

void add_egg(egg_t **head, int id, int x, int y)
{
    egg_t *egg = malloc(sizeof(egg_t));

    egg->id = id;
    egg->x = x;
    egg->y = y;
    if (!*head) {
        egg->next = NULL;
        *head = egg;
        return;
    }
    egg->next = *head;
    *head = egg;
}

void delete_egg(egg_t **head, int index)
{
    int i = 0;
    egg_t *dest = NULL;

    if (!*head)
        return;
    for (egg_t *tmp = *head; tmp; tmp = tmp->next) {
        if (i != index) {
            add_egg(&dest, tmp->id, tmp->x, tmp->y);
        }
        i ++;
    }
    free_eggs(*head);
    *head = dest;
}

egg_t *get_egg_at_index(egg_t *eggs, int index)
{
    int i = 0;
    egg_t *tmp;

    if (!eggs)
        return NULL;
    tmp = eggs;
    while (tmp) {
        if (i == index)
            break;
        i ++;
        tmp = tmp->next;
    }
    return tmp;
}

void free_eggs(egg_t *head)
{
    egg_t *tmp;

    while (head) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}
