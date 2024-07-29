/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** teams
*/

#ifndef TEAMS_H_
    #define TEAMS_H_

    #include "../server.h"

typedef struct egg_s {
    int x;
    int y;
    int id;
    struct egg_s *next;
} egg_t;

typedef struct team_s {
    char *name;
    struct egg_s *eggs;
} team_t;

/* eggs.c */
void add_egg(egg_t **head, int id, int x, int y);
void delete_egg(egg_t **head, int index);
egg_t *get_egg_at_index(egg_t *eggs, int index);
void free_eggs(egg_t *head);

/* eggs_utils.c */
int eggs_len(egg_t *head);
void assign_egg_position_to_player(egg_t **head, client_info_t *player);
void print_eggs(egg_t *eggs, int fd);

#endif /* !TEAMS_H_ */
