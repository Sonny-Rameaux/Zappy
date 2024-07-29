/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Incantation
*/

#ifndef INCANTATION_HPP_
#define INCANTATION_HPP_

#include <vector>
#include <memory>
#include "Player.hpp"

class Incantation {
    public:
        Incantation(int x, int y, int level);
        ~Incantation() = default;

        std::vector<std::shared_ptr<Player>> _incanters;
        int _x;
        int _y;
        int _level;
};

#endif /* !INCANTATION_HPP_ */
