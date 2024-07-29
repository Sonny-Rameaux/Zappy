/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** main
*/

#include "../../include/ui/Core.hpp"

int main(int ac, char **av)
{
    std::string ip;
    std::string port;

    SetTraceLogLevel(LOG_ERROR);

    if (!Core::parseArgs(ac, av, ip, port)) {
        std::cerr << "Args error.\n";
        return 84;
    }
    try {
        Core core(ip, port);
        core.mainLoop();
    } catch(...) {
        return 84;
    }
    return 0;
}
