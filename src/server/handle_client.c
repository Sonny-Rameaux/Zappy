/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myftp-vincent.montero-fontaine
** File description:
** handle_client
*/
#include "server.h"

void pop_command(log_t *logins, int i)
{
    char *last_popped = pop_front(&logins->clients[i].cmd_queue);
    double dtime;

    while (last_popped != NULL) {
        handle_commands(last_popped, logins, i);
        logins->clients[i].last_command_time = time(NULL);
        free(last_popped);
        dtime = difftime(time(NULL), logins->clients[i].last_command_time);
        if (dtime < logins->clients[i].command_delay)
            break;
        last_popped = pop_front(&logins->clients[i].cmd_queue);
    }
}

void handle_client_data(log_t *logins)
{
    int i;
    double dtime;

    for (i = 0; i < MAX_CLIENTS; i++) {
        read_client(logins, i);
        dtime = difftime(time(NULL), logins->clients[i].last_command_time);
        if (dtime >= logins->clients[i].command_delay) {
            logins->clients[i].command_delay = 0.0;
            pop_command(logins, i);
        }
    }
}

char *read_input(char *buffer, log_t *l, int i)
{
    int total_read = 0;
    int valread;

    while (1) {
        valread = read(l->clients[i].sd, buffer
            + total_read, BUFFER_SIZE - total_read);
        if (valread <= 0) {
            quit_command(l, &l->clients[i], NULL), free(buffer);
            return NULL;
        } else {
            total_read += valread;
        }
        if (total_read >= 2 && buffer[total_read - 2] == '\r'
            && buffer[total_read - 1] == '\n') {
            break;
        }
    }
    buffer[total_read] = '\0';
    return buffer;
}

void read_client(log_t *l, int i)
{
    char *buffer;
    char **arr = NULL;

    if (l->clients[i].sd > 0 && FD_ISSET(l->clients[i].sd, &l->readfds)) {
        buffer = malloc(sizeof(char) * 1024);
        buffer = read_input(buffer, l, i);
        if (buffer == NULL) {
            free(buffer);
            return;
        }
        arr = parse_cmd(buffer, "\n");
        for (int cmd_nb = 0; arr[cmd_nb]; cmd_nb++) {
            append(&l->clients[i].cmd_queue, arr[cmd_nb]);
        }
        free_arr(arr), free(buffer);
    }
}
