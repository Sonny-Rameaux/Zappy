/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Inventory
*/

#include "../../../../include/ui/Inventory.hpp"

void Inventory::addItem(std::string name, int quantity)
{
    bool isSet = false;

    for (size_t i = 0; i < this->_inv.size(); i ++) {
        if (this->_inv[i]->_name == name) {
            this->_inv[i]->_quantity += quantity;
            isSet = true;
            break;
        }
    }
    if (!isSet) {
        this->_inv.push_back(std::make_shared<Item>(name, quantity));
    }
    this->checkNegativeQ();
}

void Inventory::clear()
{
    this->_inv.clear();
}

void Inventory::checkNegativeQ()
{
    std::vector<std::shared_ptr<Item>> dest;

    for (size_t i = 0; i < this->_inv.size(); i ++) {
        if (this->_inv[i]->_quantity > 0) {
            dest.push_back(this->_inv[i]);
        }
    }
    this->_inv = dest;
}

void Inventory::clearVector(std::vector<std::string> &vector)
{
    std::vector<std::string> dest;

    for (std::size_t i = 0; i < vector.size(); i ++) {
        if (vector[i] != "")
            dest.push_back(vector[i]);
    }

    vector = dest;
}

std::vector<std::string> Inventory::parseString(std::string &str, char delim)
{
    std::vector<std::string> dest;
    std::stringstream stream(str);
    std::string token;

    while (getline(stream, token, delim)) {
        dest.push_back(token);
    }

    Inventory::clearVector(dest);
    return dest;
}

/*void Inventory::parseItem(std::string &item, std::string &name, int &quantity)
{
    std::vector<std::string> parsed = Inventory::parseString(item, '_');

    if (parsed.size() != 2) {
        name = "";
        quantity = 0;
    }
    name = parsed[0];
    quantity = std::atoi(parsed[1].c_str());
}*/
void Inventory::parseItem(std::string &item, std::string &name, int &quantity)
{
    std::vector<std::string> parsed = Inventory::parseString(item, '_');

    if (parsed.size() != 2) {
        name.clear();
        quantity = 0;
        return;
    }

    name = parsed[0];
    quantity = std::atoi(parsed[1].c_str());

    if (quantity <= 0) {
        name.clear();
        quantity = 0;
    }
}

void Inventory::display()
{
    for (size_t i = 0; i < this->_inv.size(); i ++) {
        std::cout << this->_inv[i].get()->_name << "=>" << this->_inv[i].get()->_quantity;
        if (i + 1 < this->_inv.size())
            std::cout << ", ";
    }
    std::cout << std::endl;
}

int Inventory::getQuantity(std::string name)
{
    for (size_t i = 0; i < this->_inv.size(); i ++) {
        if (this->_inv[i].get()->_name == name) {
            return this->_inv[i].get()->_quantity;
        }
    }
    return 0;
}
