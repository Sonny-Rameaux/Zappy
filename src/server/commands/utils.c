/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** utils
*/

#include "commands.h"

char *orientation_to_str(enum Orientation o)
{
    switch (o) {
        case N:
            return "N";
        case S:
            return "S";
        case W:
            return "W";
        case E:
            return "E";
        default:
            return "UNKNOWN";
    }
}
