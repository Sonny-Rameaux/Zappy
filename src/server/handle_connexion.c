/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** handle_connexion
*/
#include "server.h"

void sigint_handler(int signum)
{
    (void)signum;
    should_exit = 1;
}

void handle_signal(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    signal(SIGPIPE, SIG_IGN);
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

static void free_clients_connected(log_t *log)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (log->clients[i].sd > 0)
            quit_command(log, &log->clients[i], NULL);
    }
    log->graphic_connected = 0;
}

static void init_server(log_t *log, par_t *parsing, map_t *map, int s)
{
    log->max_sd = s;
    log->gui_map = map;
    log->parsed = parsing;
    log->client_nbs = 0;
    log->refill_delay = time(NULL);
    log->incant_data = init_incantation_prerequisites();
}

void handle_connections(int s, par_t *parsing)
{
    log_t log;
    map_t *map = create_map(parsing->width, parsing->height);

    memset(&log, 0, sizeof(log_t)), fill_map_with_resources(map);
    log.max_sd = s;
    log.gui_map = map;
    log.parsed = parsing;
    init_server(&log, parsing, map, s), handle_signal();
    while (!should_exit) {
        FD_ZERO(&log.readfds);
        FD_SET(s, &log.readfds);
        for (int i = 0; i < MAX_CLIENTS; i++)
            set_client_socket(&log, i);
        select_client(&log, s);
    }
    free_clients_connected(&log);
    free_map(map), free_incantation_prerequisites(log.incant_data);
}

static void refill_items_on_map(log_t *logins)
{
    double delay = difftime(time(NULL), logins->refill_delay);

    if (delay >= 20.0 / logins->parsed->freq) {
        fill_map_with_resources(logins->gui_map);
        logins->refill_delay = time(NULL);
    }
}

void select_client(log_t *logins, int s)
{
    int rc;
    socklen_t clientSze;
    int clientSocket;
    struct sockaddr_in clientSa;
    struct timeval tv = {.tv_sec = 0, .tv_usec = 0};

    rc = select(logins->max_sd + 1, &logins->readfds, NULL, NULL, &tv);
    if (rc < 0)
        return;
    if (FD_ISSET(s, &logins->readfds)) {
        clientSze = sizeof(clientSa);
        clientSocket = accept(s, (struct sockaddr *)&clientSa, &clientSze);
        if (clientSocket < 0)
            return;
        add_client_socket(clientSocket, logins, &clientSa);
        my_putstr_fd("WELCOME\r\n", clientSocket);
    }
    check_players_win(logins), check_players_death(logins);
    refill_items_on_map(logins), handle_client_data(logins);
}
