/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** random
*/

#include "server.h"

int gen_randint(int max)
{
    if (max == 0)
        return rand() % 1;
    return rand() % max;
}
