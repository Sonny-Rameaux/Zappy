/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** conds
*/

#include "server.h"

static void pdi_event(int graph, int cl)
{
    if (graph) {
        dprintf(
            graph,
            "pdi %d\r\n",
            cl
        );
    }
}

static void check_players_death_bis(client_info_t *client, log_t *server)
{
    double delay = difftime(time(NULL), client->life_timer);

    if (delay < client->life_delay)
        return;
    if (is_item_in_inventory(client->inventory, "food")) {
        add_item_to_inventory(client->inventory, "food", -1);
        client->life_timer = time(NULL);
        return;
    }
    dprintf(client->sd, "dead\r\n");
    pdi_event(server->graphic_connected, client->sd);
    quit_command(NULL, client, NULL);
}

void check_players_death(log_t *logins)
{
    for (size_t i = 0; i < MAX_CLIENTS; i ++) {
        if (logins->clients[i].logged_in && !logins->clients[i].is_graphic)
            check_players_death_bis(&logins->clients[i], logins);
    }
}

static void check_player_win(client_info_t *client, log_t *server)
{
    if (client->level < 8)
        return;
    if (server->graphic_connected) {
        dprintf(
            server->graphic_connected,
            "seg %s\r\n",
            client->team_name
        );
    }
    should_exit = 1;
}

void check_players_win(log_t *logins)
{
    for (size_t i = 0; i < MAX_CLIENTS; i ++) {
        if (logins->clients[i].logged_in && !logins->clients[i].is_graphic) {
            check_player_win(&logins->clients[i], logins);
        }
    }
}
