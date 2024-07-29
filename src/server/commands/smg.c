/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** smg
*/

#include "commands.h"

void smg(int graph, char *msg)
{
    if (graph) {
        dprintf(
            graph,
            "smg %s\r\n",
            msg
        );
    }
}
