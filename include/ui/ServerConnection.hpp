/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** ServerConnection
*/

#pragma once
#include <tuple>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <fcntl.h>
#include <cstdlib>
#include <exception>
#include <cstdio>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <sstream>


namespace zap
{
    class ServerConnection {
        public:
            ServerConnection() : _socket(-1), _x(0), _y(0), _address(nullptr) {}
            ServerConnection(int port, const char *name);
            ~ServerConnection();
            std::tuple<int, int> getSize();
            void getBoardContent();
            bool extractCoordinates(const std::string& cmd, int& x, int& y);
            int getWidth();
            int getHeight();
            int getSocket() const;
        protected:
        private:
            int _socket;
            std::vector<std::string> _tiles;
            bool _connected;
            int _x;
            int _y;
            struct sockaddr_in *_address;
    };
} // namespace zap

