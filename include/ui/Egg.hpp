/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Egg
*/

#ifndef EGG_HPP_
#define EGG_HPP_

#include <string>
#include "Model.hpp"

class Egg {
    public:
        Egg(std::string id, int x, int y);
        void Draw();
        ~Egg() = default;

        zap::EModel _model;
        std::string _id;
        int _x;
        int _y;
};

#endif /* !EGG_HPP_ */
