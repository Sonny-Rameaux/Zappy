/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** arr
*/
#include "server.h"

void free_arr(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i]; i++) {
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}

int size_arr(char **arr)
{
    int i = 0;

    if (!arr)
        return i;
    for (; arr[i]; i++);
    return i;
}
