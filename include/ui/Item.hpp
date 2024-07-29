/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Item
*/

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include <string>

class Item {
    public:
        Item(std::string name, int quantity);
        ~Item() = default;

        std::string _name;
        int _quantity;
};

#endif /* !ITEM_HPP_ */
