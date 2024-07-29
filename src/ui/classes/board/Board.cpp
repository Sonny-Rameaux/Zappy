/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** Board
*/

#include "../../../../include/ui/Board.hpp"
#include <iostream>

zap::Board::Board(int x, int z, float space)
{
    float Posx = -x;
    float Posz = -z;
    _x = x;
    _z = z;
    Color color = WHITE;
    std::vector<zap::Case> line;
    for (int j = 0;j < z; Posz+=2, j++) {
        for (int i = 0 ;i < x; Posx+=2, color = !color, i++) {
            line.push_back(zap::Case({Posx, 0, Posz}, color));
            Posx+=space;
        }
        _board.push_back(line);
        line.clear();
        Posx = -x;
        Posz += space;
    }

    for (size_t i = 0; i < 8; i ++) {
        this->_levels[i + 1] = 0;
    }
}

Vector3 zap::Board::getPos(int z, int x)
{
    if(x >= _board.size())
        x = _board.size() - 1;
    if(z >= _board[x].size())
        z = _board[x].size() - 1;
    return _board[x][z].getPos();
};

void zap::Board::Draw()
{
    for (size_t i = 0; i < _board.size(); i++) {
        for (size_t j = 0; j < _board[i].size(); j++) {
            _board[i][j].Draw();
        }
    }
    for (size_t i = 0; i < _teams.size(); i++) {
        if (_teams[i]) {
            _teams[i]->display_players();
        }
    }
    for (size_t i = 0; i < _eggs.size(); i++) {
        if (_eggs[i]) {
            _eggs[i]->Draw();
        }
    }
}

bool zap::Board::teamExists(std::string &name)
{
    for (size_t i = 0; i < this->_teams.size(); i ++) {
        if (this->_teams[i]->_name == name)
            return true;
    }
    return false;
}

std::shared_ptr<Team> zap::Board::getTeam(std::string &name)
{
    for (size_t i = 0; i < this->_teams.size(); i ++) {
        if (this->_teams[i]->_name == name)
            return this->_teams[i];
    }

    return nullptr;
}

std::shared_ptr<Player> zap::Board::getPlayer(std::string &id)
{
    std::shared_ptr<Player> player;

    for (size_t i = 0; i < this->_teams.size(); i ++) {
        player = this->_teams[i]->getPlayer(id);
        if (player != nullptr)
            return player;
    }

    return nullptr;
}

std::shared_ptr<Egg> zap::Board::getEgg(std::string &id)
{
    std::shared_ptr<Egg> egg;

    for (size_t i = 0; i < this->_eggs.size(); i ++) {
        if (this->_eggs[i]->_id == id)
            return this->_eggs[i];
    }

    return nullptr;
}

void zap::Board::deletePlayer(std::string &id)
{
    for (size_t i = 0; i < this->_teams.size(); i ++) {
        if (this->_teams[i]->playerExists(id)) {
            this->_teams[i]->deletePlayer(id);
            break;
        }
    }
}

void zap::Board::deleteEgg(std::string &id)
{
    std::vector<std::shared_ptr<Egg>> dest;

    for (size_t i = 0; i < this->_eggs.size(); i ++) {
        if (this->_eggs[i]->_id != id) {
            dest.push_back(this->_eggs[i]);
        }
    }

    this->_eggs = dest;
}

void zap::Board::deleteIncantation(int x, int y)
{
    std::vector<std::shared_ptr<Incantation>> _dest;

    for (size_t i = 0; i < this->_incantations.size(); i ++) {
        if (this->_incantations[i]->_x != x || this->_incantations[i]->_y != y) {
            _dest.push_back(this->_incantations[i]);
        }
    }

    this->_incantations = _dest;
}

void zap::Board::addIncantation(int x, int y, int level)
{
    this->_incantations.push_back(std::make_shared<Incantation>(Incantation(x, y, level)));
}

void zap::Board::addIncanter(int x, int y, std::shared_ptr<Player> player)
{
    for (size_t i = 0; i < this->_incantations.size(); i ++) {
        if (this->_incantations[i]->_x == x && this->_incantations[i]->_y == y) {
            this->_incantations[i]->_incanters.push_back(player);
        }
    }
}

std::shared_ptr<Incantation> zap::Board::getIncantation(int x, int y)
{
    for (const auto& incantation : this->_incantations) {
        if (incantation && incantation->_x == x && incantation->_y == y) {
            return incantation;
        }
    }

    return nullptr;
}

void zap::Board::update()
{
    for (size_t i = 0; i < this->_board.size(); i ++) {
        for (size_t j = 0; j < this->_board[i].size(); j ++) {
            this->_board[i][j].Update();
        }
    }
}

void zap::Board::display_teams()
{
    for (size_t i = 0; i < this->_teams.size(); i ++) {
        std::cout << this->_teams[i]->_name << ": " << std::endl;
        this->_teams[i]->display_players();
        std::cout << std::endl << std::endl;
    }
}

void zap::Board::display_eggs()
{
    for (size_t i = 0; i < this->_eggs.size(); i ++) {
        std::cout
        << this->_eggs[i]->_id
        << " "
        << this->_eggs[i]->_x
        << ";"
        << this->_eggs[i]->_y
        << std::endl;
    }
}

Color zap::Board::getCurrentColor()
{
    Color color;

    if (this->_colorPallet.size() == 0)
        return WHITE;
    color = this->_colorPallet[this->_currentColor];
    this->_currentColor ++;
    if (this->_currentColor >= this->_colorPallet.size())
        this->_currentColor = 0;

    return color;
}
