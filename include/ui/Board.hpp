/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** Board
*/

#pragma once

#include <vector>
#include <map>

#include "Case.hpp"
#include "Cube.hpp"
#include "ADrawable.hpp"
#include "Team.hpp"
#include "Incantation.hpp"

enum GAMESTATE {
    PROCESSING = 0,
    ENDED
};

namespace zap
{
    class Board : public ADrawable {
        public:
            Board(int x, int z, float space);

            ~Board() = default;
            Vector3 getPos(int z, int x);
            int x(){ return _x;}
            int z(){ return _z;}
            std::vector<std::vector<zap::Case>> getBoard();
            void Draw() override;
            void update();
            void display_teams();
            void display_eggs();

            int _x;
            int _z;
            std::vector<std::vector<zap::Case>> _board;
            bool teamExists(std::string &name);
            std::shared_ptr<Team> getTeam(std::string &name);

            std::shared_ptr<Player> getPlayer(std::string &id);
            void deletePlayer(std::string &id);
            void deleteEgg(std::string &id);
            std::shared_ptr<Egg> getEgg(std::string &id);

            std::shared_ptr<Incantation> getIncantation(int x, int y);
            void deleteIncantation(int x, int y);
            void addIncantation(int x, int y, int level);
            void addIncanter(int x, int y, std::shared_ptr<Player> player);

            Color getCurrentColor();

            double freq;
            std::vector<std::shared_ptr<Egg>> _eggs;
            std::vector<std::shared_ptr<Team>> _teams;
            std::vector<std::shared_ptr<Incantation>> _incantations;
            std::vector<Color> _colorPallet = {
                GRAY,
                DARKGRAY,
                YELLOW,
                GOLD,
                ORANGE,
                PINK,
                RED,
                MAROON,
                GREEN,
                LIME,
                DARKGREEN,
                SKYBLUE,
                BLUE,
                DARKBLUE,
                PURPLE,
                VIOLET,
                DARKPURPLE,
                BEIGE,
                BROWN,
                DARKBROWN
            };
            size_t _currentColor = 0;
            GAMESTATE _state = PROCESSING;
            std::map<size_t, size_t> _levels;
            std::string _winner = "";
    };
} // namespace zap

Color operator!(Color color);
