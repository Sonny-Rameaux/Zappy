/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Egg
*/

#include "../../../../include/ui/Egg.hpp"

Egg::Egg(std::string id, int x, int y)
    : _model({(float)x, (float)y, 0})
{
    this->_id = id;
    this->_x = x;
    this->_y = y;
}

void Egg::Draw()
{
    _model.Draw();
}
