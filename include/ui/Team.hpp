/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Team
*/

#ifndef TEAM_HPP_
#define TEAM_HPP_

#include <string>
#include <vector>
#include <memory>

#include "Player.hpp"

class Team {
    public:
        Team(std::string name, Color color);
        ~Team() = default;

        bool playerExists(std::string &id);
        std::shared_ptr<Player> getPlayer(std::string &id);
        void deletePlayer(std::string &id);
        void display_players();

        std::string _name;
        std::vector<std::shared_ptr<Player>> _players;
        Color _color;
};

#endif /* !TEAM_HPP_ */
