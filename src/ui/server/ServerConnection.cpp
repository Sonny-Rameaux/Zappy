/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** ServerConnection
*/
#include "../../../include/ui/ServerConnection.hpp"
#include <unistd.h>  

zap::ServerConnection::ServerConnection(int port, const char *name)
{
    _socket = socket(PF_INET, SOCK_STREAM, 0);
    if (_socket == -1) throw std::runtime_error("Failed to create socket");
    
    _address = new sockaddr_in;
    _address->sin_addr.s_addr = inet_addr(name);
    _address->sin_family = AF_INET;
    _address->sin_port = htons(port);
    if (connect(_socket, (const sockaddr *)(_address), sizeof(struct sockaddr_in)) == -1) {
        delete _address;
        throw std::runtime_error("Failed to connect");
    }

    if (write(_socket, "GRAPHIC\r\n", 9) == -1) {
        delete _address;
        close(_socket);
        throw std::runtime_error("Failed to write initial command");
    } else {
        char buf[9];
        read(_socket, buf, 9);
    }
}

int zap::ServerConnection::getWidth() { return _x; }

int zap::ServerConnection::getHeight() { return _y; }

bool zap::ServerConnection::extractCoordinates(const std::string& cmd, int& x, int& y) {
    std::istringstream iss(cmd);
    if (iss >> x >> y) {
        return true;
    } else {
        return false;
    }
}

std::tuple<int, int> zap::ServerConnection::getSize()
{

    std::string cmd;
    char buf = 0;
    int error = 0;
    int x = 0, y = 0;

    for (error = read(_socket, &buf, 1);buf != '\n' && buf != '\r';read(_socket, &buf, 1)) {
        if (error == 0) throw std::runtime_error("Connection closed by server");
        if (error == -1) throw std::runtime_error("Error reading from socket");
        cmd += buf;
    }
    extractCoordinates(cmd, x, y);
    _x = x;
    _y = y;
    _tiles.resize(x * y);
    return std::make_tuple(x, y);
}

void zap::ServerConnection::getBoardContent()
{
    if (write(_socket, "mct\r\n", 5) == -1) {
        throw std::runtime_error("Failed to send content command");
    }

    std::string currentLine;
    char buf[1024];
    ssize_t bytesRead;
    bool isLastLine = false;

    _tiles.clear();

    while (!isLastLine) {
        bytesRead = read(_socket, buf, sizeof(buf) - 1);
        if (bytesRead == -1) {
            throw std::runtime_error("Error reading from socket");
        }
        if (bytesRead == 0) {
            throw std::runtime_error("Connection closed by server");
        }

        buf[bytesRead] = '\0';
        currentLine.append(buf, bytesRead);

        std::size_t pos;
        while ((pos = currentLine.find_first_of("\r\n")) != std::string::npos) {
            std::string line = currentLine.substr(0, pos);
            if (pos + 1 < currentLine.size() && currentLine[pos] == '\r' && currentLine[pos + 1] == '\n') {
                isLastLine = true;
                currentLine.erase(0, pos + 2);
            } else {
                currentLine.erase(0, pos + 1);
            }

            if (line.empty()) {
                continue;
            }

            std::istringstream iss(line);
            std::string component;
            std::string items;

            for (int i = 0; i < 3; i++) {
                if (!(iss >> component)) {
                    throw std::runtime_error("Error parsing line: " + line);
                }
            }

            while (iss >> component) {
                items += component;
            }

            _tiles.push_back(items);

            if (isLastLine) {
                break;
            }
        }
    }
}

zap::ServerConnection::~ServerConnection()
{
    close(_socket);
    if (_address) {
        delete _address;
    }
    _tiles.clear();
}
