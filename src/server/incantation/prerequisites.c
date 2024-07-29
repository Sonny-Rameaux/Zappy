/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** prerequisites
*/

#include "incantation.h"

static void init_ip0(incant_prereq_t *ip)
{
    ip[0].n_players = 1;
    ip[0].req_lvl = 1;
    ip[0].inv = malloc(sizeof(inv_t));
    ip[0].inv->items = NULL;
    add_item_to_inventory(ip[0].inv, "linemate", 1);
}

static void init_ip1(incant_prereq_t *ip)
{
    ip[1].n_players = 2;
    ip[1].req_lvl = 2;
    ip[1].inv = malloc(sizeof(inv_t));
    ip[1].inv->items = NULL;
    add_item_to_inventory(ip[1].inv, "linemate", 1);
    add_item_to_inventory(ip[1].inv, "deraumere", 1);
    add_item_to_inventory(ip[1].inv, "sibur", 1);
}

static void init_ip2(incant_prereq_t *ip)
{
    ip[2].n_players = 2;
    ip[2].req_lvl = 3;
    ip[2].inv = malloc(sizeof(inv_t));
    ip[2].inv->items = NULL;
    add_item_to_inventory(ip[2].inv, "linemate", 2);
    add_item_to_inventory(ip[2].inv, "sibur", 1);
    add_item_to_inventory(ip[2].inv, "phiras", 2);
}

static void init_ip3(incant_prereq_t *ip)
{
    ip[3].n_players = 4;
    ip[3].req_lvl = 4;
    ip[3].inv = malloc(sizeof(inv_t));
    ip[3].inv->items = NULL;
    add_item_to_inventory(ip[3].inv, "linemate", 1);
    add_item_to_inventory(ip[3].inv, "deraumere", 1);
    add_item_to_inventory(ip[3].inv, "sibur", 2);
    add_item_to_inventory(ip[3].inv, "phiras", 1);
}

static void init_ip4(incant_prereq_t *ip)
{
    ip[4].n_players = 4;
    ip[4].req_lvl = 5;
    ip[4].inv = malloc(sizeof(inv_t));
    ip[4].inv->items = NULL;
    add_item_to_inventory(ip[4].inv, "linemate", 1);
    add_item_to_inventory(ip[4].inv, "deraumere", 2);
    add_item_to_inventory(ip[4].inv, "sibur", 1);
    add_item_to_inventory(ip[4].inv, "mendiane", 3);
}

static void init_ip5(incant_prereq_t *ip)
{
    ip[5].n_players = 6;
    ip[5].req_lvl = 6;
    ip[5].inv = malloc(sizeof(inv_t));
    ip[5].inv->items = NULL;
    add_item_to_inventory(ip[5].inv, "linemate", 1);
    add_item_to_inventory(ip[5].inv, "deraumere", 2);
    add_item_to_inventory(ip[5].inv, "sibur", 3);
    add_item_to_inventory(ip[5].inv, "phiras", 1);
}

static void init_ip6(incant_prereq_t *ip)
{
    ip[6].n_players = 6;
    ip[6].req_lvl = 7;
    ip[6].inv = malloc(sizeof(inv_t));
    ip[6].inv->items = NULL;
    add_item_to_inventory(ip[6].inv, "linemate", 2);
    add_item_to_inventory(ip[6].inv, "deraumere", 2);
    add_item_to_inventory(ip[6].inv, "sibur", 2);
    add_item_to_inventory(ip[6].inv, "mendiane", 2);
    add_item_to_inventory(ip[6].inv, "phiras", 2);
    add_item_to_inventory(ip[6].inv, "thystame", 1);
}

incant_prereq_t *init_incantation_prerequisites(void)
{
    incant_prereq_t *ip = malloc(sizeof(incant_prereq_t) * (MAX_IP + 1));

    init_ip0(ip);
    init_ip1(ip);
    init_ip2(ip);
    init_ip3(ip);
    init_ip4(ip);
    init_ip5(ip);
    init_ip6(ip);
    return ip;
}

void free_incantation_prerequisites(incant_prereq_t *ip)
{
    for (size_t i = 0; i < MAX_IP; i ++) {
        free_items(ip[i].inv->items);
        free(ip[i].inv);
    }
    free(ip);
}
