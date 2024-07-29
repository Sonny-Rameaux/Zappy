/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** incantation
*/

#include "incantation.h"

static bool check_incantation(char **args)
{
    return size_arr(args) == 0;
}

static bool good_incant_player(client_info_t target, client_info_t *current)
{
    if (!target.logged_in)
        return false;
    if (target.is_graphic)
        return false;
    if (target.pos_x != current->pos_x)
        return false;
    if (target.pos_y != current->pos_y)
        return false;
    if (target.level != current->level)
        return false;
    return true;
}

static int get_n_incanters(log_t *server, client_info_t *client)
{
    int n = 0;

    for (int i = 0; i < MAX_CLIENTS; i ++) {
        if (good_incant_player(server->clients[i], client))
            n ++;
    }
    return n;
}

static client_info_t **assign_incanters(
    int n, log_t *server,
    client_info_t *client
)
{
    client_info_t **incanters = malloc(sizeof(client_info_t *) * (n + 1));
    int j = 0;

    for (int i = 0; i < MAX_CLIENTS && j < n; i ++) {
        if (good_incant_player(server->clients[i], client)) {
            incanters[j] = &((server->clients)[i]);
            j ++;
        }
    }
    incanters[j] = NULL;
    return incanters;
}

static bool check_incant_items(inv_t *incanter_inv, inv_t *prerequisites)
{
    for (item_t *tmp = prerequisites->items; tmp; tmp = tmp->next) {
        if (!is_item_in_inventory(incanter_inv, tmp->name))
            return false;
    }
    return true;
}

static void pic_event(
    log_t *server,
    client_info_t **incanters,
    client_info_t *initial
)
{
    char buffer[4444] = {0};
    size_t offset = 0;

    for (int i = 0; incanters[i] != NULL; i ++)
        offset +=
            snprintf(
                buffer + offset,
                sizeof(buffer),
                " %d",
                incanters[i]->sd
            );
    if (server->graphic_connected)
        dprintf(
            server->graphic_connected,
            "pic %d %d %d%s\r\n",
            initial->pos_x,
            initial->pos_y,
            initial->level,
            buffer
        );
}

static void pie_event(log_t *server, client_info_t *client, bool status)
{
    if (server->graphic_connected) {
        dprintf(
            server->graphic_connected,
            "pie %d %d %d\r\n",
            client->pos_x,
            client->pos_y,
            status
        );
    }
}

static void exec_incantation(
    client_info_t **incanters,
    client_info_t *client,
    incant_prereq_t prereq,
    log_t *server
)
{
    for (int i = 0; incanters[i] != NULL; i ++)
        incanters[i]->level += 1;
    for (item_t *tmp = prereq.inv->items; tmp; tmp = tmp->next)
        add_item_to_inventory(client->inventory, tmp->name, -tmp->quantity);
    for (int i = 0; incanters[i] != NULL; i ++) {
        dprintf(
            incanters[i]->sd,
            "Elevation underway\nCurrent level: %d\r\n",
            incanters[i]->level
        );
        incanters[i]->delay = 300.0 / server->parsed->freq;
    }
}

static bool check_prerequisites(log_t *server, client_info_t *client)
{
    int elevation = client->level - 1;
    int n_incanters = get_n_incanters(server, client);
    client_info_t **incanters = assign_incanters(n_incanters, server, client);

    pic_event(server, incanters, client);
    if (elevation < 0 || elevation >= 8)
        return false;
    if (!check_incant_items(
            client->inventory,
            server->incant_data[elevation].inv
        ))
        return false;
    if (n_incanters != server->incant_data[elevation].n_players)
        return false;
    exec_incantation(incanters, client,
        server->incant_data[elevation], server);
    free(incanters);
    return true;
}

void incantation_command(log_t *server, client_info_t *client, char **args)
{
    if (!check_incantation(args)) {
        dprintf(1, "raté l'incantation départ sd: %d\n", client->sd);
        KO_OUTPUT(client->sd);
        return;
    }
    if (!check_prerequisites(server, client)) {
        KO_OUTPUT(client->sd);
        pie_event(server, client, false);
        dprintf(1, "raté l'incantation sd: %d\n", client->sd);
        return;
    }
    dprintf(1, "CURRENT CLI LEVEL: %d, SD: %d\n", client->level, client->sd);
    pie_event(server, client, true);
}
