/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Team
*/

#include "../../../../include/ui/Team.hpp"

Team::Team(std::string name, Color color)
{
    this->_name = name;
    this->_color = color;
}

bool Team::playerExists(std::string &id)
{
    for (size_t i = 0; i < this->_players.size(); i ++) {
        if (this->_players[i]->_id == id)
            return true;
    }
    return false;
}

std::shared_ptr<Player> Team::getPlayer(std::string &id)
{
    for (size_t i = 0; i < this->_players.size(); i ++) {
        if (this->_players[i]->_id == id)
            return this->_players[i];
    }
    return nullptr;
}

void Team::deletePlayer(std::string &id)
{
    std::vector<std::shared_ptr<Player>> dest;

    for (size_t i = 0; i < this->_players.size(); i ++) {
        if (this->_players[i]->_id != id) {
            dest.push_back(this->_players[i]);
        }
    }
    this->_players = dest;
}

void Team::display_players()
{
    for (size_t i = 0; i < this->_players.size(); i ++) {
        _players[i].get()->Draw();
    }
}
