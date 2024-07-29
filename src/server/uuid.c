/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-vincent.montero-fontaine
** File description:
** uuid
*/
#include "server.h"

char *escape_special_characters(const char *input)
{
    int len = strlen(input);
    char *output = malloc(2 * len + 1);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == '"' || input[i] == '\\') {
            output[j] = '\\';
            j++;
        }
        output[j] = input[i];
        j++;
    }
    output[j] = '\0';
    return output;
}
