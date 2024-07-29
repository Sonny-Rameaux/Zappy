/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** MenuPlayer
*/

#include "../../../../include/ui/MenuPlayer.hpp"

zap::MenuPlayer::MenuPlayer(Texture2D texture, Vector2 position, Board &board)
    : menuTexture(texture), menuPosition(position), info(board)
{
    icone.push_back(LoadTexture("assets/food.png"));
    icone.push_back(LoadTexture("assets/linemate.png"));
    icone.push_back(LoadTexture("assets/deraumere.png"));
    icone.push_back(LoadTexture("assets/sibur.png"));
    icone.push_back(LoadTexture("assets/mendiane.png"));
    icone.push_back(LoadTexture("assets/phiras.png"));
    icone.push_back(LoadTexture("assets/thystame.png"));
    idTeam = 0;
    idPlayer = 0;
}

zap::MenuPlayer::~MenuPlayer()
{
    UnloadTexture(menuTexture);
}

void zap::MenuPlayer::Update(int key)
{
    if (key == KEY_E) {
        if (show == true) {
            show = false;
            return;
        } if (show == false) {
            show = true;
            return;
        }
    } if (key == KEY_I) {
        if (idPlayer > 0) {
            idPlayer--;
            return;
        } if (idTeam > 0) {
            idTeam--;
            idPlayer = info._teams.at(idTeam).get()->_players.size() - 1;
        }
    } if (key == KEY_O) {
        std::cout << idTeam << " " << info._teams.size() << std::endl;
        int max = info._teams.at(idTeam).get()->_players.size();
        if (idPlayer < max - 1) {
            idPlayer++;
            return;
        } if (idTeam < info._teams.size() - 1) {
            idTeam++;
            idPlayer = 0;
        }
    }
}

void zap::MenuPlayer::Draw()
{
    if (info._teams.size() <= 0) {
        show = false;
        return;
    }
    std::shared_ptr<Team> team = info._teams.at(idTeam);
    if (team.get()->_players.size() == 0) show = false;

    if (!show) return;

    std::shared_ptr<Player> player = team.get()->_players.at(idPlayer);
    Inventory inventory = player.get()->_inv;

    std::stringstream steam;
    steam << team.get()->_name;
    std::string nameTeam = steam.str();
    std::stringstream splayer;
    splayer << player.get()->_id;
    std::string namePlayer = splayer.str();
    std::stringstream splayerlevel;
    splayerlevel << player.get()->_level;
    std::string levelPlayer = splayerlevel.str();
    std::stringstream spos;
    spos << "x" << player.get()->_x + 1 << "/ y" << player.get()->_y + 1;
    std::string positionPlayer = spos.str();

    DrawTexture(menuTexture, menuPosition.x, menuPosition.y, WHITE);
    DrawText(namePlayer.c_str(), menuPosition.x + 210, menuPosition.y + 60, 30, BLACK);
    DrawText(nameTeam.c_str(), menuPosition.x + 85, menuPosition.y + 85, 20, team.get()->_color);
    DrawText(levelPlayer.c_str(), menuPosition.x + 240, menuPosition.y + 95, 20, BLACK);
    DrawText(positionPlayer.c_str(), menuPosition.x + (menuTexture.width - 140), menuPosition.y + 110, 24, BLACK);

    Vector2 pos_init = { menuPosition.x + 50, menuPosition.y + 165 };
    const char* itemNames[] = {"Food", "Linemate", "Deraumere", "Sibur", "Mendiane", "Phiras", "Thystame"};

    for (int i = 0; i < icone.size(); i++) {
        Vector2 pos = { pos_init.x, pos_init.y + (60 * i) };
        DrawTextureEx(icone[i], pos, 0.0f, 0.3f, WHITE);
        std::stringstream itemText;
        itemText << itemNames[i];
        switch (i) {
        case 0:
            itemText << " " << inventory.getQuantity("food");
            break;
        case 1:
            itemText << " " << inventory.getQuantity("linemate");
            break;
        case 2:
            itemText << " " << inventory.getQuantity("deraumere");
            break;
        case 3:
            itemText << " " << inventory.getQuantity("sibur");
            break;
        case 4:
            itemText << " " << inventory.getQuantity("mendiane");
            break;
        case 5:
            itemText << " " << inventory.getQuantity("phiras");
            break;
        case 6:
            itemText << " " << inventory.getQuantity("thystame");
            break;
        default:
            break;
        }
        DrawText(itemText.str().c_str(), pos.x + 60, pos.y + 20, 20, BLACK);
    }
}
