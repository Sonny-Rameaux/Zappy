/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** parse_cmd
*/
#include "server.h"

static int count_tokens(char *tmp, const char *sep)
{
    size_t count = 0;
    char *token = NULL;
    char *tmp_copy = strdup(tmp);

    if (tmp_copy == NULL) {
        return -1;
    }
    token = strtok(tmp_copy, sep);
    while (token) {
        count++;
        token = strtok(NULL, sep);
    }
    free(tmp_copy);
    return count;
}

static char *copy_parsed_cmd(const char *token)
{
    size_t len = strlen(token);
    char *dest = malloc(len + 2);

    if (dest == NULL) {
        return NULL;
    }
    strcpy(dest, token);
    dest[len] = '\n';
    dest[len + 1] = '\0';
    return dest;
}

char **check_destination(char *tmp, char *tmp_copy, char *sep, char **dest)
{
    int n_tokens = count_tokens(tmp, sep);

    if (n_tokens == -1) {
        free(tmp), free(tmp_copy);
        return NULL;
    }
    dest = malloc(sizeof(char *) * (n_tokens + 1));
    if (dest == NULL) {
        free(tmp), free(tmp_copy);
        return NULL;
    }
    return dest;
}

char **free_error(char **dest, char *tmp, char *tmp_copy, size_t i)
{
    for (size_t j = 0; j < i; j++)
        free(dest[j]);
    free(dest), free(tmp), free(tmp_copy);
    return NULL;
}

char **parse_cmd(char *cmd, char *sep)
{
    char **dest = NULL;
    char *token = NULL;
    char *tmp = strdup(cmd);
    char *tmp_copy = strdup(cmd);
    size_t i = 0;

    dest = check_destination(tmp, tmp_copy, sep, dest);
    if (dest == NULL)
        return NULL;
    token = strtok(tmp_copy, sep);
    for (i = 0; token; i++) {
        dest[i] = copy_parsed_cmd(token);
        if (dest[i] == NULL)
            return free_error(dest, tmp, tmp_copy, i);
        token = strtok(NULL, sep);
    }
    dest[i] = NULL;
    free(tmp), free(tmp_copy);
    return dest;
}
