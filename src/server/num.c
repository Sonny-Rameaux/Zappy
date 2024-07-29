/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** num
*/

#include "server.h"

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

bool is_num(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i ++) {
        if (!is_digit(str[i])) {
            return false;
        }
    }
    return true;
}
