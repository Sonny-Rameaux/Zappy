/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** handle_command
*/
#include "server.h"

const command_t COMMANDS_LIST[] = {
    {"Forward", forward_command},
    {"Inventory", inventory_command},
    {"Take", take_command},
    {"Set", set_command},
    {"Right", right_command},
    {"Left", left_command},
    {"Look", look},
    {"Eject", eject_command},
    {"Connect_nbr", connect_nbr_command},
    {"Fork", fork_command},
    {"Broadcast", broadcast_command},
    {"Incantation", incantation_command},
    {"debug", debug_command},
    {"quit", quit_command},
    {NULL, NULL}
};

const command_t GUI_CMDS_LIST[] = {
    {"msz", msz_command},
    {"ppo", ppo_command},
    {"plv", plv_command},
    {"ppa", ppa_command},
    {"epa", epa_command},
    {"pin", pin_command},
    {"bct", bct_command},
    {"mct", mct_command},
    {"tna", tna_command},
    {"sgt", sgt_command},
    {"sst", sst_command},
    {"quit", quit_command},
    {NULL, NULL}
};

void parse_line(const char *line, char *username, char *uuid)
{
    char *token;
    char temp[strlen(line) + 1];

    strcpy(temp, line);
    token = strtok(temp, "--");
    if (token != NULL) {
        strcpy(username, token);
    } else {
        strcpy(username, "");
    }
    token = strtok(NULL, "");
    if (token != NULL && token[0] == '-') {
        strcpy(uuid, token + 1);
    } else {
        strcpy(uuid, token);
    }
}

static int check_graphics_command(log_t *server, char **args, int i, int count)
{
    for (int j = 0; GUI_CMDS_LIST[j].name; j++) {
        if (strcmp(args[0], GUI_CMDS_LIST[j].name) == 0) {
            GUI_CMDS_LIST[j].func(server, &server->clients[i], &args[1]);
            free_tokenize(args, count);
            return 1;
        }
    }
    return 0;
}

static int check_command(char **args, log_t *server, int i, int count)
{
    if (server->clients[i].is_graphic) {
        if (check_graphics_command(server, args, i, count) == 1)
            return 1;
        return 0;
    }
    for (int j = 0; COMMANDS_LIST[j].name; j++) {
        if (strcmp(args[0], COMMANDS_LIST[j].name) == 0) {
            COMMANDS_LIST[j].func(server, &server->clients[i], &args[1]);
            free_tokenize(args, count);
            return 1;
        }
    }
    return 0;
}

void handle_commands(char *command, log_t *server, int i)
{
    char **args = NULL;
    int count;

    if (command == NULL || command[0] == '\0') {
        dprintf(server->clients[i].sd, "ko\r\n");
        return;
    }
    if (!server->clients[i].logged_in) {
        assign_team(command, server, i);
        return;
    }
    args = tokenize(command, &count);
    add_null_terminator(&args, &count), trim_newline(args[0]);
    if (check_command(args, server, i, count))
        return;
    free_tokenize(args, count), dprintf(server->clients[i].sd, "ko\r\n");
}
