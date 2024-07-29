/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** cmdParsing
*/

#include "../../../include/ui/CmdParsing.hpp"

std::map<std::string, void (*)(std::vector<std::string>, zap::Board&)> cmdMap = {
    {"msz", CmdParsing::msz},
    {"bct", CmdParsing::bct},
    {"tna", CmdParsing::tna},
    {"pnw", CmdParsing::pnw},
    {"ppo", CmdParsing::ppo},
    {"plv", CmdParsing::plv},
    {"pin", CmdParsing::pin},
    {"pex", CmdParsing::pex},
    {"pbc", CmdParsing::pbc},
    {"pic", CmdParsing::pic},
    {"pie", CmdParsing::pie},
    {"pfk", CmdParsing::pfk},
    {"pdr", CmdParsing::pdr},
    {"pgt", CmdParsing::pgt},
    {"pdi", CmdParsing::pdi},
    {"enw", CmdParsing::enw},
    {"ebo", CmdParsing::ebo},
    {"edi", CmdParsing::edi},
    {"sgt", CmdParsing::sgt},
    {"sst", CmdParsing::sst},
    {"seg", CmdParsing::seg},
    {"smg", CmdParsing::smg},
    {"suc", CmdParsing::tna},
    {"sbp", CmdParsing::tna}
};

void CmdParsing::execCmd(std::string name, std::vector<std::string> args, zap::Board &board)
{
    std::cout << "[" << name <<"]";
    for (size_t i = 0; i < args.size(); i ++) {
        std::cout << " " << args[i];
    }
    std::cout << std::endl;

    if (cmdMap.find(name) == cmdMap.end()) {
        std::cerr << "Unknown command." << std::endl;
        return;
    }
    cmdMap[name](args, board);
}

void CmdParsing::msz(std::vector<std::string> args, zap::Board &board)
{
    int x, z;

    if (args.size() != 2)
        return;

    x = std::atoi(args[0].c_str());
    z = std::atoi(args[1].c_str());

    board = zap::Board(x, z, 1);
}

/*void CmdParsing::bct(std::vector<std::string> args, zap::Board &board)
{
    int x, y;

    if (args.size() < 2)
        return;

    x = std::atoi(args[0].c_str());
    y = std::atoi(args[1].c_str());

    board._board[y][x]._inv.clear();
    for (size_t i = 2; i < args.size(); i ++) {
        std::string name = "";
        int quantity = 0;
        boost::erase_all(args[i], ",");
        Inventory::parseItem(args[i], name, quantity);
        if (name != "" && quantity > 0) {
            board._board[y][x]._inv.addItem(name, quantity);
        }
    }
}*/
void CmdParsing::bct(std::vector<std::string> args, zap::Board &board)
{
    if (args.size() < 2) {
        return;
    }

    int x = std::atoi(args[0].c_str());
    int y = std::atoi(args[1].c_str());

    if (x < 0 || x >= board.x() || y < 0 || y >= board.z()) {
        return;
    }

    size_t nEggs = board._board[y][x]._inv.getQuantity("egg");
    board._board[y][x]._inv.clear();
    board._board[y][x]._inv.addItem("egg", nEggs);

    for (size_t i = 2; i < args.size(); i++) {
        std::string name;
        int quantity = 0;
        boost::erase_all(args[i], ",");

        Inventory::parseItem(args[i], name, quantity);

        if (!name.empty() && quantity > 0) {
            board._board[y][x]._inv.addItem(name, quantity);
        } else {
            continue;
        }
    }
}

void CmdParsing::tna(std::vector<std::string> args, zap::Board &board)
{
    if (args.size() != 1)
        return;

    if (!board.teamExists(args[0])) {
        board._teams.push_back(
            std::make_shared<Team>(
                args[0],
                board.getCurrentColor()
            )
        );
    }
}

void CmdParsing::pnw(std::vector<std::string> args, zap::Board &board)
{
    std::shared_ptr<Team> team;

    if (args.size() != 6)
        return;

    if ((team = board.getTeam(args[5])) == nullptr)
        return;
    std::cout << args[3]<< std::endl << std::endl << std::endl << std::endl;

    team->_players.push_back(
        std::make_shared<Player>(
            team->_name,
            args[0],
            Player::stringToOrient(args[3]),
            std::atoi(args[1].c_str()),
            std::atoi(args[2].c_str()),
            std::atoi(args[4].c_str()),
            BLUE
        )
    );
}

void CmdParsing::ppo(std::vector<std::string> args, zap::Board &board)
{
    std::shared_ptr<Player> player;

    if (args.size() != 4)
        return;

    if ((player = board.getPlayer(args[0])) == nullptr)
        return;

    player->_x = std::atoi(args[1].c_str());
    player->_y = std::atoi(args[2].c_str());
    player->_orientation = Player::stringToOrient(args[3]);
}

void CmdParsing::plv(std::vector<std::string> args, zap::Board &board)
{
    std::shared_ptr<Player> player;

    if (args.size() != 2)
        return;

    if ((player = board.getPlayer(args[0])) == nullptr)
        return;

    player->_level = std::atoi(args[1].c_str());
}

void CmdParsing::pin(std::vector<std::string> args, zap::Board &board)
{
    std::shared_ptr<Player> player;
    std::string name;
    int quantity;

    if (args.size() < 3)
        return;

    if ((player = board.getPlayer(args[0])) == nullptr)
        return;

    player->_x = std::atoi(args[1].c_str());
    player->_y = std::atoi(args[2].c_str());

    player->_inv.clear();
    for (size_t i = 3; i < args.size(); i ++) {
        boost::erase_all(args[i], ",");
        Inventory::parseItem(args[i], name, quantity);
        if (name != "" && quantity > 0) {
            player->_inv.addItem(name, quantity);
        }
    }
}

void CmdParsing::pex(std::vector<std::string> args, zap::Board &board)
{
    //! ppo
}

void CmdParsing::pbc(std::vector<std::string> args, zap::Board &board)
{
    //! visuel ou chat
}

void CmdParsing::pic(std::vector<std::string> args, zap::Board &board)
{
    int x, y, level;

    if (args.size() < 4)
        return;

    x = std::atoi(args[0].c_str());
    y = std::atoi(args[1].c_str());
    level = std::atoi(args[2].c_str());

    board.deleteIncantation(x, y);
    board.addIncantation(x, y, level);

    for (size_t i = 3; i < args.size(); i ++) {
        board.addIncanter(x, y, board.getPlayer(args[i]));
    }
}

void CmdParsing::pie(std::vector<std::string> args, zap::Board &board)
{
    int x, y;
    bool status;
    std::shared_ptr<Incantation> incantation;

    if (args.size() != 3)
        return;

    x = std::atoi(args[0].c_str());
    y = std::atoi(args[1].c_str());
    status = std::atoi(args[2].c_str());

    if (!status) {
        board.deleteIncantation(x, y);
        return;
    }

    incantation = board.getIncantation(x, y);
    if (!incantation)
        return;
    for (size_t i = 0; i < incantation->_incanters.size(); i ++) {
        incantation->_incanters[i]->_level ++;
    }
    board.deleteIncantation(x, y);
}

void CmdParsing::pfk(std::vector<std::string> args, zap::Board &board)
{
    //! visuel
}

void CmdParsing::pdr(std::vector<std::string> args, zap::Board &board)
{
    int x, y;
    std::shared_ptr<Player> player;

    if (args.size() != 2)
        return;

    if ((player = board.getPlayer(args[0])) == nullptr)
        return;

    x = player->_x;
    y = player->_y;

    player->_inv.addItem(args[1], -1);
    board._board[y][x]._inv.addItem(args[1], 1);
}

void CmdParsing::pgt(std::vector<std::string> args, zap::Board &board)
{
    int x, y;
    std::shared_ptr<Player> player;

    if (args.size() != 2)
        return;

    if ((player = board.getPlayer(args[0])) == nullptr)
        return;

    x = player->_x;
    y = player->_y;

    board._board[y][x]._inv.addItem(args[1], -1);
    player->_inv.addItem(args[1], 1);
}

void CmdParsing::pdi(std::vector<std::string> args, zap::Board &board)
{
    if (args.size() != 1)
        return;

    board.deletePlayer(args[0]);
}

void CmdParsing::enw(std::vector<std::string> args, zap::Board &board)
{
    int x, y;

    if (args.size() != 4)
        return;

    x = std::atoi(args[2].c_str());
    y = std::atoi(args[3].c_str());

    board._eggs.push_back(std::make_shared<Egg>(args[0], x, y));
    board._board[y][x]._inv.addItem("egg", 1);
}

void CmdParsing::ebo(std::vector<std::string> args, zap::Board &board)
{
    std::shared_ptr<Egg> egg;

    if (args.size() != 1)
        return;

    if ((egg = board.getEgg(args[0])) == nullptr)
        return;

    board._board[egg->_y][egg->_x]._inv.addItem("egg", 1);
    board.deleteEgg(args[0]);
}

void CmdParsing::edi(std::vector<std::string> args, zap::Board &board)
{
    std::shared_ptr<Egg> egg;

    if (args.size() != 1)
        return;

    if ((egg = board.getEgg(args[0])) == nullptr)
        return;

    board._board[egg->_y][egg->_x]._inv.addItem("egg", 1);
    board.deleteEgg(args[0]);
}

void CmdParsing::sgt(std::vector<std::string> args, zap::Board &board)
{
    if (args.size() != 1)
        return;

    board.freq = std::atof(args[0].c_str());
}

void CmdParsing::sst(std::vector<std::string> args, zap::Board &board)
{
    if (args.size() != 1)
        return;

    board.freq = std::atof(args[0].c_str());
}

void CmdParsing::seg(std::vector<std::string> args, zap::Board &board)
{
    if (args.size() != 1)
        return;

    board._winner = args[0];
    board._state = ENDED;
}

void CmdParsing::smg(std::vector<std::string> args, zap::Board &board)
{
    //! chat
}

void CmdParsing::suc(std::vector<std::string> args, zap::Board &board)
{
    //! rien
}

void CmdParsing::sbp(std::vector<std::string> args, zap::Board &board)
{
    //! rien
}
