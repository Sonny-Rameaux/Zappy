/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** process_arguments
*/

#include "server.h"

static void free_teams(team_t **teams)
{
    if (!teams)
        return;
    for (size_t i = 0; teams[i] != NULL; i ++) {
        free_eggs(teams[i]->eggs);
        free(teams[i]->name);
        free(teams[i]);
    }
    free(teams);
}

static void init_parsing(par_t *parsing)
{
    parsing->port = 4242;
    parsing->width = 10;
    parsing->height = 10;
    parsing->clientsNb = 5;
    parsing->freq = 100;
    parsing->egg_n = 0;
    parsing->teams = malloc(3 * sizeof(team_t *));
    if (parsing->teams == NULL)
        exit(84);
    for (int i = 0; i < 2; i++) {
        parsing->teams[i] = malloc(sizeof(team_t));
        if (parsing->teams[i] == NULL)
            exit(84);
        parsing->teams[i]->name = malloc(6 * sizeof(char));
        if (parsing->teams[i]->name == NULL)
            exit(84);
        snprintf(parsing->teams[i]->name, 6, "Team%d", i + 1);
        parsing->teams[i]->eggs = NULL;
    }
    parsing->teams[2] = NULL;
}

static void process_n(int argc, char **argv, int optind, par_t *parsing)
{
    int teamCount = 0;
    int i;

    for (i = optind - 1; i < argc && argv[i][0] != '-'; i++)
        teamCount++;
    if (teamCount <= 0)
        exit(84);
    parsing->teams = malloc((teamCount + 1) * sizeof(team_t *));
    if (parsing->teams == NULL)
        exit(84);
    for (i = 0; i < teamCount; i++) {
        parsing->teams[i] = malloc(sizeof(team_t));
        parsing->teams[i]->name = strdup(argv[optind - 1 + i]);
        parsing->teams[i]->eggs = NULL;
    }
    parsing->teams[teamCount] = NULL;
    optind += teamCount - 1;
}

static void check_port(char *arg, par_t *par)
{
    if (!has_all_digits(arg)) {
        fprintf(stderr, "Usage: ./zappy_server -p PORT -x WIDTH -y HEIGHT ");
        fprintf(stderr, "-n team1 team2 -c nbClientsPerTeam -f frequency\n");
        free_server(par);
        exit(84);
    }
    par->port = atoi(arg);
}

static void check_arg(char *arg, par_t *par)
{
    if (!has_all_digits(arg)) {
        fprintf(stderr, "Usage: ./zappy_server -p PORT -x WIDTH -y HEIGHT ");
        fprintf(stderr, "-n team1 team2 -c nbClientsPerTeam -f frequency\n");
        free_server(par);
        exit(84);
    }
}

static void process_next_options(par_t *par, char opt, char *arg)
{
    switch (opt) {
        case 'c':
            check_arg(arg, par);
            par->clientsNb = atoi(arg);
            break;
        case 'f':
            check_arg(arg, par);
            par->freq = atoi(arg);
            break;
        default:
            fprintf(stderr, "Usage: ./zappy_server -p PORT -x WIDTH -y ");
            fprintf(stderr, "HEIGHT -n team1 team2 -c nbClientsPerTeam -f ");
            fprintf(stderr, "frequency\n"), free_server(par);
            exit(84);
    }
}

static void process_option(par_t *par, char opt, char *arg)
{
    int value;

    switch (opt) {
        case 'p':
            check_port(arg, par);
            break;
        case 'x':
            check_arg(arg, par);
            value = atoi(arg);
            par->width = value <= 0 ? 1 : value;
            break;
        case 'y':
            check_arg(arg, par);
            value = atoi(arg);
            par->height = value <= 0 ? 1 : value;
            break;
        default:
            process_next_options(par, opt, arg);
    }
}

static void assign_eggs_to_teams(par_t *parsing)
{
    for (int i = 0; parsing->teams[i] != NULL; i ++) {
        for (int j = 0; j < parsing->clientsNb; j ++) {
            add_egg(
                &parsing->teams[i]->eggs,
                parsing->egg_n,
                gen_randint(parsing->width),
                gen_randint(parsing->height)
            );
            parsing->egg_n ++;
        }
    }
}

void parse_arguments(int argc, char **argv, par_t *par)
{
    int opt;

    init_parsing(par);
    opt = getopt(argc, argv, "p:x:y:n:c:f:");
    while (opt != -1) {
        switch (opt) {
            case 'n':
                free_teams(par->teams), process_n(argc, argv, optind, par);
                break;
            default:
                process_option(par, opt, optarg);
                break;
        }
        opt = getopt(argc, argv, "p:x:y:n:c:f:");
    }
    if (par->height <= 0 && par->width <= 0)
        free_server(par), exit(84);
    assign_eggs_to_teams(par);
}
