/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <vector>
#include <string>
#include "Model.hpp"
#include "Inventory.hpp"
#include "Egg.hpp"

enum Orien {
    N,
    E,
    S,
    W
};

class Player
{
    public:
        Player(
            std::string team,
            std::string id,
            Orien ori,
            int x,
            int y,
            int lvl,
            Color color
        );
        ~Player() = default;

        void Draw();
        void Rotate();

        static Orien stringToOrient(std::string &ori);
        static std::string orienToString(Orien &ori);

        std::string _id;
        std::string _team;
        Orien _orientation = S;
        int _level;
        int _x;
        int _y;
        Inventory _inv;

        zap::PModel _model;
        // std::vector<int> _color;
        // sprite _sprite
};

#endif /* !PLAYER_HPP_ */
