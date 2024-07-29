/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** eggs_utils
*/

#include "teams.h"

int eggs_len(egg_t *head)
{
    int i = 0;

    for (egg_t *tmp = head; tmp; tmp = tmp->next)
        i ++;
    return i;
}

void assign_egg_position_to_player(egg_t **head, client_info_t *player)
{
    if (!*head)
        return;
    player->pos_x = (*head)->x;
    player->pos_y = (*head)->y;
    player->life_timer = time(NULL);
    delete_egg(&*head, 0);
}

void print_eggs(egg_t *eggs, int fd)
{
    for (egg_t *tmp = eggs; tmp; tmp = tmp->next) {
        dprintf(fd, "%d;%d\n", tmp->x, tmp->y);
    }
}
