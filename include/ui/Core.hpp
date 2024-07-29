/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <raylib.h>
#include <unistd.h>
#include <vector>

#include "Board.hpp"
#include "Camera.hpp"
#include "Cube.hpp"
#include "Model.hpp"
#include "Window.hpp"
#include "ServerConnection.hpp"
#include "Clock.hpp"
#include "CmdParsing.hpp"
#include "connection.hpp"
#include "MenuCase.hpp"
#include "MenuPlayer.hpp"

#define HELPTXT "Déplacer de la caméra : Z / Q / S / D\nAfficher/cacher les panneaux infos : A / E\nFaire défiler les infos des joueurs : I / O";

class Core {
    public:
        Core(std::string ip, std::string port);
        ~Core() = default;

        static bool parseArgs(int ac, char **av, std::string &ip, std::string &port);
        static std::vector<std::string> parseString(std::string &str, char delim);
        static void clearVector(std::vector<std::string> &vector);

        void initialCommunication();

        void mainLoop();
        void processingLoop();
        void endedLoop();

        void communication();
        void sendPlayerCommand(const std::string &cmd, std::string &id);
        void sendCommands();
        void receiveCommands();

        void events();
        void cameraEvents();
        void mCaseEvents();
        void mPlayerEvents();

        void update();
        void updateTimer();
        void updatePlayers();
        void updateEggs();
        void updateStats();

        void display();
        void drawTexts();

        std::string getStatsText();
        std::string getFreqText();

    protected:
    private:
        TCPClient _client;

        zap::Window _window;
        zap::Camera _camera;
        zap::Board _board {10, 10, 1};

        Clock _clTimer;
        Clock _clUpd;
        Clock _clCam;
        Clock _clmct;
        Clock _clpla;
        Clock _clsgt;

        zap::MenuPlayer _mPlayer;
        zap::MenuCase _mCase;
        int _xCase = 0;
        int _zCase = 0;
        std::string _helptxt = HELPTXT;
        std::string _timertxt;
};

#endif /* !CORE_HPP_ */
