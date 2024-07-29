/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Tile
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include <vector>

class Tile
{
    public:
        Tile();
        ~Tile();

        std::vector<int> getPos() { return pos; };
        int getFood() { return food; };
        int getLinemate() { return linemate; };
        int getDeraumere() { return deraumere; };
        int getSibur() { return sibur; };
        int getMendiane() { return mendiane; };
        int getPhiras() { return phiras; };
        int getThystame() { return thystame; };
        bool getEgg() { return egg; };

        void setPos(int x, int y) { pos[0] = x; pos[1] = y; };
        void setFood(int new_food) { food = new_food; };
        void setLinemate(int new_linemate) { linemate = new_linemate; };
        void setDeraumere(int new_deraumere) { deraumere = new_deraumere; };
        void setSibur(int new_sibur) { sibur = new_sibur; };
        void setMendiane(int new_mendiane) { mendiane = new_mendiane; };
        void setPhiras(int new_phiras) { phiras = new_phiras; };
        void setThystame(int new_thystame) { thystame = new_thystame; };
        void setEgg(bool new_egg) { egg = new_egg; };

    private:
        std::vector<int> pos;
        int food;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
        int egg;
};

#endif /* !TILE_HPP_ */
