/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** CmdParsing
*/

#ifndef CMDPARSING_HPP_
#define CMDPARSING_HPP_

#include <map>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

#include "Board.hpp"

class CmdParsing {
    public:
        static void execCmd(std::string name, std::vector<std::string> args, zap::Board &board);

        static void msz(std::vector<std::string> args, zap::Board &board);
        static void bct(std::vector<std::string> args, zap::Board &board);
        static void tna(std::vector<std::string> args, zap::Board &board);
        static void pnw(std::vector<std::string> args, zap::Board &board);
        static void ppo(std::vector<std::string> args, zap::Board &board);
        static void plv(std::vector<std::string> args, zap::Board &board);
        static void pin(std::vector<std::string> args, zap::Board &board);
        static void pex(std::vector<std::string> args, zap::Board &board);
        static void pbc(std::vector<std::string> args, zap::Board &board);
        static void pic(std::vector<std::string> args, zap::Board &board);
        static void pie(std::vector<std::string> args, zap::Board &board);
        static void pfk(std::vector<std::string> args, zap::Board &board);
        static void pdr(std::vector<std::string> args, zap::Board &board);
        static void pgt(std::vector<std::string> args, zap::Board &board);
        static void pdi(std::vector<std::string> args, zap::Board &board);
        static void enw(std::vector<std::string> args, zap::Board &board);
        static void ebo(std::vector<std::string> args, zap::Board &board);
        static void edi(std::vector<std::string> args, zap::Board &board);
        static void sgt(std::vector<std::string> args, zap::Board &board);
        static void sst(std::vector<std::string> args, zap::Board &board);
        static void seg(std::vector<std::string> args, zap::Board &board);
        static void smg(std::vector<std::string> args, zap::Board &board);
        static void suc(std::vector<std::string> args, zap::Board &board);
        static void sbp(std::vector<std::string> args, zap::Board &board);
};

#endif /* !CMDPARSING_HPP_ */
