/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Core
*/

#include "../../../../include/ui/Core.hpp"

Core::Core(std::string ip, std::string port)
    :   _client(ip.c_str(), port.c_str()),
        _mCase(LoadTexture("assets/invotory_cube.png"), {0.0, 0.0}, _board),
        _mPlayer(LoadTexture("assets/invotory_player.png"), {(float)(GetScreenWidth() - 477), 0.0}, _board)
{
    if (!this->_client.connectToServer())
        throw std::string("Server error");

    this->initialCommunication();
}

bool Core::parseArgs(int ac, char **av, std::string &ip, std::string &port)
{
    bool portSet = false;
    bool ipSet = false;

    if (!av || !av[0])
        return false;
    for (int i = 1; av[i] != NULL; i ++) {
        if (std::string(av[i]) == "-p" && av[i + 1] != NULL) {
            port = std::string(av[i + 1]);
            portSet = true;
        } else if (std::string(av[i]) == "-h" && av[i + 1] != NULL) {
            ip = std::string(av[i + 1]);
            ipSet = true;
        }
        if (ipSet && portSet)
            break;
    }
    if (!ipSet || !portSet)
        return false;
    return true;
}

void Core::clearVector(std::vector<std::string> &vector)
{
    std::vector<std::string> dest;

    for (std::size_t i = 0; i < vector.size(); i ++) {
        if (vector[i] != "")
            dest.push_back(vector[i]);
    }

    vector = dest;
}

std::vector<std::string> Core::parseString(std::string &str, char delim)
{
    std::vector<std::string> dest;
    std::stringstream stream(str);
    std::string token;

    while (getline(stream, token, delim)) {
        dest.push_back(token);
    }

    Core::clearVector(dest);
    return dest;
}

void Core::mainLoop()
{
    while (!WindowShouldClose()) {
        switch(this->_board._state) {
            case PROCESSING:
                this->processingLoop();
                break;
            case ENDED:
            default:
                this->endedLoop();
                break;
        }
    }
    CloseWindow();
}

void Core::processingLoop()
{
    if (this->_client.getConnected())
        this->communication();
    this->events();
    this->update();
    this->display();
}

void Core::endedLoop()
{
    this->update();

    BeginDrawing();
    ClearBackground(BLUE);
    DrawText(
        std::string(
            "Winner: " + this->_board._winner
        ).c_str(),
        GetScreenWidth() / 2 - 425,
        GetScreenHeight() / 2 - 400,
        150,
        GOLD
    );
    DrawText(
        this->getStatsText().c_str(),
        GetScreenWidth() / 2 - 50,
        GetScreenHeight() / 2 - 100,
        75,
        GOLD
    );
    DrawFPS(10, 10);
    EndDrawing();
}

void Core::initialCommunication()
{
    this->_client.receiveWelcomeMessage();
    this->_client.sendStaticMessage("GRAPHIC");
    this->_client.receiveAndParseMapSize();
    this->_client.sendStaticMessage("msz");
    this->_client.sendStaticMessage("tna");
    this->_client.sendStaticMessage("ppa");
    this->_client.sendStaticMessage("epa");
}

void Core::communication()
{
    this->sendCommands();
    this->receiveCommands();
}

void Core::sendPlayerCommand(const std::string &cmd, std::string &id)
{
    std::string result = cmd + " " + id;

    this->_client.sendStaticMessage(result);
}

void Core::sendCommands()
{
    if (this->_clmct.getValueInSeconds() >= 0.25) {
        this->_client.sendStaticMessage("mct");
        this->_clmct.reset();
    }

    // //! utile ?
    // if (this->_clsgt.getValueInSeconds() >= 5.0) {
    //     this->_client.sendStaticMessage("sgt");
    //     this->_clsgt.reset();
    // }

    if (this->_clpla.getValueInSeconds() >= 0.1) {
        for (size_t i = 0; i < this->_board._teams.size(); i ++) {
            for (size_t j = 0; j < this->_board._teams[i]->_players.size(); j ++) {

                this->sendPlayerCommand(
                    "ppo",
                    this->_board._teams[i]->_players[j]->_id
                );

                this->sendPlayerCommand(
                    "pin",
                    this->_board._teams[i]->_players[j]->_id
                );

                this->sendPlayerCommand(
                    "plv",
                    this->_board._teams[i]->_players[j]->_id
                );

            }
        }
        this->_clpla.reset();
    }
}

void Core::receiveCommands()
{
    this->_client.handleServerResponse();
    std::string brutMsg = this->_client.getReceivedData();
    std::vector<std::string> brutCmds = Core::parseString(brutMsg, '\r');
    std::vector<std::string> parsedCmd;
    std::string cmdName;

    for (size_t i = 0; i < brutCmds.size(); i ++) {
        boost::erase_all(brutCmds[i], "\n");

        if (brutCmds[i].size() <= 0)
            continue;

        parsedCmd = Core::parseString(brutCmds[i], ' ');
        if (parsedCmd.size() <= 0)
            continue;

        cmdName = parsedCmd[0];
        parsedCmd.erase(parsedCmd.begin());
        CmdParsing::execCmd(cmdName, parsedCmd, this->_board);
    }
}

void Core::events()
{
    this->cameraEvents();
    this->mCaseEvents();
    this->mPlayerEvents();
}

void Core::cameraEvents()
{
    if (this->_clCam.getValueInSeconds() >= 0.01) {
        this->_camera.APressed();
        this->_camera.DPressed();
        this->_camera.SPressed();
        this->_camera.WPressed();
        this->_clCam.reset();
    }
}

void Core::mCaseEvents()
{
    if (IsKeyPressed(KEY_DOWN)) {
        if (this->_zCase < this->_board._z - 1)
            this->_zCase ++;
        this->_mCase.setAncienCube(this->_xCase, this->_zCase);
    }
    if (IsKeyPressed(KEY_UP)) {
        if (this->_zCase > 0)
            this->_zCase --;
        this->_mCase.setAncienCube(this->_xCase, this->_zCase);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        if (this->_xCase < this->_board._x - 1)
            this->_xCase ++;
        this->_mCase.setAncienCube(this->_xCase, this->_zCase);
    }
    if (IsKeyPressed(KEY_LEFT)) {
        if (this->_xCase > 0)
            this->_xCase --;
        this->_mCase.setAncienCube(this->_xCase, this->_zCase);
    }
    if (IsKeyPressed(KEY_Q)) {
        this->_mCase.Update();
    }
    this->_mCase.setSelect(this->_xCase, this->_zCase);
}

void Core::mPlayerEvents()
{
    if (IsKeyPressed(KEY_E)) {
        this->_mPlayer.Update(KEY_E);
    }
    if (IsKeyPressed(KEY_I)) {
        this->_mPlayer.Update(KEY_I);
    }
    if (IsKeyPressed(KEY_O)) {
        this->_mPlayer.Update(KEY_O);
    }
}

void Core::update()
{
    if (this->_clUpd.getValueInSeconds() < 0.1)
        return;
    this->_clUpd.reset();

    this->_board.update();
    this->updatePlayers();
    this->updateEggs();
    this->updateStats();
    this->updateTimer();
}

void Core::updateTimer()
{
    double seconds = this->_clTimer.getValueInSeconds();
    this->_timertxt = std::to_string(seconds);
}

void Core::updatePlayers()
{
    for (size_t i = 0; i < this->_board._teams.size(); i++) {
        for (size_t j = 0; j < this->_board._teams[i]->_players.size(); j++) {
            this->_board._teams[i]->_players[j]->_model.setPos(
                this->_board.getPos(
                    this->_board._teams[i]->_players[j]->_x,
                    this->_board._teams[i]->_players[j]->_y
                )
            );
        }
    }
}

void Core::updateEggs()
{
    for (size_t j = 0; j < this->_board._eggs.size(); j++) {
        this->_board._eggs[j]->_model.setPos(
            this->_board.getPos(
                this->_board._eggs[j]->_x,
                this->_board._eggs[j]->_y
            )
        );
    }
}

void Core::updateStats()
{
    for (size_t i = 0; i < 8; i ++) {
        this->_board._levels[i + 1] = 0;
    }

    for (size_t i = 0; i < this->_board._teams.size(); i ++) {
        for (size_t j = 0; j < this->_board._teams[i]->_players.size(); j ++) {
            if (this->_board._teams[i]->_players[j]->_level <= 0
                || this->_board._teams[i]->_players[j]->_level > 8)
                continue;
            this->_board._levels[this->_board._teams[i]->_players[j]->_level]
                = this->_board._levels[this->_board._teams[i]->_players[j]->_level] + 1;
        }
    }
}

std::string Core::getStatsText()
{
    std::stringstream out;

    for (size_t i = 0; i < 8; i ++) {
        out
        << (i + 1)
        << ":\t"
        << this->_board._levels[i + 1]
        << std::endl;
    }

    return out.str();
}

// std::string Core::getFreqText()
// {
//     return std::to_string(this->_board.freq);
// }

void Core::display()
{
    BeginDrawing();
    BeginMode3D(this->_camera.getCam());
    ClearBackground(BLUE);
    this->_board.Draw();
    EndMode3D();
    this->_mCase.Draw();
    this->_mPlayer.Draw();
    this->drawTexts();
    DrawFPS(10, 10);
    EndDrawing();
}

void Core::drawTexts()
{
    // DrawText(
    //     this->getFreqText().c_str(),
    //     GetScreenWidth() - 100,
    //     GetScreenHeight() - 450,
    //     20,
    //     GOLD
    // );
    DrawText(
        this->_timertxt.c_str(),
        GetScreenWidth() - 150,
        GetScreenHeight() - 100,
        30,
        GOLD
    );
    DrawText(
        this->getStatsText().c_str(),
        20,
        GetScreenHeight() - 450,
        30,
        GOLD
    );
    DrawText(
        this->_helptxt.c_str(),
        20,
        GetScreenHeight() - 160,
        30,
        GOLD
    );
}
