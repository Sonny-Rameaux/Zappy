/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** server
*/

#include "server.h"

static int create_socket(int argc, char **argv)
{
    if (argc == 2 && strcmp(argv[1], "-help") == 0) {
        printf("USAGE: ./zappy_server -p port -x width -y height -n ");
        printf("name1 name2 ... -c clientsNb -f freq\n");
        exit(0);
    }
    return socket(PF_INET, SOCK_STREAM, 0);
}

static void set_client_values(
    client_info_t *client,
    int clSock,
    struct sockaddr_in *clientSa,
    double frequence
)
{
    client->sd = clSock;
    client->logged_in = 0;
    client->team_name = NULL;
    client->cmd_queue = NULL;
    client->pos_x = 0;
    client->pos_y = 0;
    client->level = 1;
    client->orient = E;
    client->address = *clientSa;
    client->last_command_time = time(NULL);
    client->life_timer = time(NULL);
    client->life_delay = 126.0 / frequence;
    client->command_delay = 0.0;
    client->delay = 0.0;
    client->is_graphic = 0;
    client->inventory = malloc(sizeof(inv_t));
    client->inventory->items = NULL;
    add_item_to_inventory(client->inventory, "food", 10);
}

void add_client_socket(
    int clSock, log_t *logins,
    struct sockaddr_in *clientSa
)
{
    logins->client_nbs += 1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (logins->clients[i].sd == 0) {
            set_client_values(
                &logins->clients[i],
                clSock, clientSa,
                logins->parsed->freq
            );
            break;
        }
    }
    if (clSock > logins->max_sd)
        logins->max_sd = clSock;
    DP_NCO(
        clSock,
        inet_ntoa(clientSa->sin_addr),
        ntohs(clientSa->sin_port)
    );
}

void print_parsed(par_t *parsing)
{
    DP_PARSE(parsing->clientsNb, parsing->freq,
        parsing->height, parsing->width, parsing->port);
    for (size_t i = 0; parsing->teams[i] != NULL; i ++) {
        printf("team_name: %s unused_slot : %d\n", parsing->teams[i]->name,
            eggs_len(parsing->teams[i]->eggs));
    }
}

void free_server(par_t *parsing)
{
    egg_t *current_egg;
    egg_t *temp;

    if (!parsing || !parsing->teams)
        return;
    for (int i = 0; parsing->teams[i]; i++) {
        free(parsing->teams[i]->name);
        current_egg = parsing->teams[i]->eggs;
        while (current_egg != NULL) {
            temp = current_egg;
            current_egg = current_egg->next;
            free(temp);
        }
        free(parsing->teams[i]);
    }
    free(parsing->teams);
}

int main(int argc, char **argv)
{
    int on = 1;
    int s = create_socket(argc, argv);
    par_t parsing;

    parse_arguments(argc, argv, &parsing);
    if (s < 0)
        return 84;
    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof on) < 0)
        return 84;
    if (bind_socket(s, &parsing) < 0)
        return 84;
    if (start_listening(s) < 0)
        return 84;
    srand(time(NULL)), handle_connections(s, &parsing), close(s);
    free_server(&parsing);
    return 0;
}

/*int main()
{
    client_info_t receiver;
    receiver.pos_x = 1;
    receiver.pos_y = 1;
    receiver.orient = N;

    client_info_t sender;
    sender.pos_x = 1;
    sender.pos_y = 2;
    sender.orient = E;
    map_t map = {3, 3, NULL};

    int direction = get_dir(&receiver, &sender, &map);
    printf("Direction: %d\n", direction);
    return 0;
}*/
