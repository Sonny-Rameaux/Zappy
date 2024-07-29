/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** MenuCase
*/

#include "../../../../include/ui/MenuCase.hpp"

zap::MenuCase::MenuCase(Texture2D texture, Vector2 position, Board &board)
    : menuTexture(texture), menuPosition(position), info(board)
{
    icone.push_back(LoadTexture("assets/food.png"));
    icone.push_back(LoadTexture("assets/linemate.png"));
    icone.push_back(LoadTexture("assets/deraumere.png"));
    icone.push_back(LoadTexture("assets/sibur.png"));
    icone.push_back(LoadTexture("assets/mendiane.png"));
    icone.push_back(LoadTexture("assets/phiras.png"));
    icone.push_back(LoadTexture("assets/thystame.png"));
    icone.push_back(LoadTexture("assets/egg.png"));
    select = { 0, 0 };
    ancienCube = info._board[select.y][select.x]._case.getColor();
    ancienPosition = { 0, 0 };
}

zap::MenuCase::~MenuCase()
{
    UnloadTexture(menuTexture);
}

void zap::MenuCase::setSelect(float x, float z)
{
    select = { x, z };
    info._board[select.y][select.x]._case.setColor(GOLD);
}

void zap::MenuCase::setAncienCube(float x, float z)
{
    info._board[ancienPosition.y][ancienPosition.x]._case.setColor(ancienCube);
    ancienPosition = { x, z };
    ancienCube = info._board[z][x]._case.getColor();
}

void zap::MenuCase::Update()
{
    if (show == true) {
        show = false;
        return;
    } if (show == false) {
        show = true;
        return;
    }
}

void zap::MenuCase::Draw()
{
    if (!show) return;

    Inventory inventory = info._board[select.y][select.x]._inv;

    std::stringstream ss;
    ss << "x" << select.x + 1 << "/ y" << select.y + 1;
    std::string positionText = ss.str();

    DrawTexture(menuTexture, menuPosition.x, menuPosition.y, WHITE);
    DrawText(positionText.c_str(), menuTexture.width - 140, menuPosition.y + 110, 24, BLACK);

    Vector2 pos_init = { menuPosition.x + 50, menuPosition.y + 70 };
    const char* itemNames[] = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame", "Egg"};

    for (int i = 0; i < icone.size(); i++) {
        Vector2 pos = { pos_init.x, pos_init.y + (60 * i) };
        DrawTextureEx(icone[i], pos, 0.0f, 0.3f, WHITE);
        std::stringstream itemText;
        itemText << itemNames[i];
        switch (i) {
        case 0:
            itemText << " " << inventory.getQuantity("food") << "/" << getTotalQuantity("food");
            break;
        case 1:
            itemText << " " << inventory.getQuantity("linemate") << "/" << getTotalQuantity("linemate");
            break;
        case 2:
            itemText << " " << inventory.getQuantity("deraumere") << "/" << getTotalQuantity("deraumere");
            break;
        case 3:
            itemText << " " << inventory.getQuantity("sibur") << "/" << getTotalQuantity("sibur");
            break;
        case 4:
            itemText << " " << inventory.getQuantity("mendiane") << "/" << getTotalQuantity("mendiane");
            break;
        case 5:
            itemText << " " << inventory.getQuantity("phiras") << "/" << getTotalQuantity("phiras");
            break;
        case 6:
            itemText << " " << inventory.getQuantity("thystame") << "/" << getTotalQuantity("thystame");
            break;
        case 7:
            itemText << " " << inventory.getQuantity("egg") << "/" << getTotalQuantity("egg");
            break;
        default:
            break;
        }
        DrawText(itemText.str().c_str(), pos.x + 60, pos.y + 20, 20, BLACK);
    }
}

int zap::MenuCase::getTotalQuantity(std::string name)
{
    int quantity = 0;

    for (int y = 0; y < info._board.size(); y++) {
        for (int x = 0; x < info._board[y].size(); x++) {
            Inventory inventory = info._board[y][x]._inv;
            quantity += inventory.getQuantity(name);
        }
    }
    return quantity;
}
