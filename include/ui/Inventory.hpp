/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Inventory
*/

#ifndef INVENTORY_HPP_
#define INVENTORY_HPP_

#include "Item.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <sstream>

class Inventory {
    public:
        Inventory() = default;
        ~Inventory() = default;

        void addItem(std::string name, int quantity);
        void clear();
        void display();

        int getQuantity(std::string name);
        std::vector<std::shared_ptr<Item>> getInv() { return _inv; };

        static void parseItem(std::string &item, std::string &name, int &quantity);

        std::vector<std::shared_ptr<Item>> _inv;
    protected:
    private:
        void checkNegativeQ();

        static std::vector<std::string> parseString(std::string &str, char delim);
        static void clearVector(std::vector<std::string> &vector);

};

#endif /* !INVENTORY_HPP_ */
