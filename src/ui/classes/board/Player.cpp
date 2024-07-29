/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Player
*/

#include "../../../../include/ui/Player.hpp"

Player::Player(
    std::string team,
    std::string id,
    Orien ori,
    int x,
    int y,
    int lvl,
    Color color
) : _model({0, 0, 0}, color)
{
    this->_team = team;
    this->_id = id;
    this->_orientation = ori;
    this->_level = lvl;
    this->_x = x;
    this->_y = y;
}

Orien Player::stringToOrient(std::string &ori)
{
    if (ori == "N")
        return N;
    if (ori == "E")
        return E;
    if (ori == "S")
        return S;
    if (ori == "W")
        return W;
    return S;
}

std::string Player::orienToString(Orien &ori)
{
    if (ori == N)
        return "N";
    if (ori == E)
        return "E";
    if (ori == S)
        return "S";
    if (ori == W)
        return "W";
    return "S";
}

void Player::Rotate()
{
    float rotAngle = 0.0f;
    switch (_orientation) {
        case N:
            rotAngle = 180;
            break;
        case S:
            rotAngle = 0;
            break;
        case E:
            rotAngle = 90;
            break;
        case W:
            rotAngle = 270;
            break;
        default:
            break;
    }
    _model._angle = rotAngle;
}

void Player::Draw()
{
    Rotate();
    _model.Draw();
}
