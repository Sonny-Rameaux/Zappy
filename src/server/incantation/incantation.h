/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** incantation
*/

#ifndef INCANTATION_H_
    #define INCANTATION_H_

    #include "../server.h"
    #include "../inventory/inventory.h"

    #define MAX_IP 7

typedef struct incant_prereq_s {
    int n_players;
    int req_lvl;
    struct inv_s *inv;
} incant_prereq_t;

/* prerequisites.c */
incant_prereq_t *init_incantation_prerequisites(void);
void free_incantation_prerequisites(incant_prereq_t *ip);

/* incantation.h */
void incantation_command(log_t *server, client_info_t *client, char **args);

#endif /* !INCANTATION_H_ */
