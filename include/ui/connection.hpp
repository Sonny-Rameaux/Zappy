/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** connexion
*/

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
#include <stdexcept>
#include <string>
#include <cstring>
#include <boost/algorithm/string.hpp>

const int BUFFER_SIZE = 1024;

class TCPClient {
    public:
        TCPClient(const char *ip, const char *port);
        ~TCPClient();

        bool connectToServer();

        void startCommunication();

        int getWidth() { return _x; };
        int getHeight() { return _y; };
        int getConnected() { return connected; };
        void setConnected(int value) { connected = value; };

        void handleInitialServerResponse();
        void handleServerResponse();
        void sendStaticMessage(const std::string& msg);

        void receiveWelcomeMessage();
        void receiveAndParseMapSize();

        std::string getReceivedData() const;
        void clearReceivedData();
        void parseMCTResponse(const std::string& response);
        void printTiles() const;
    private:
        const char *server_ip;
        const char *server_port;
        int client_socket;
        bool connected = true;
        std::vector<std::string> _tiles;
        std::string receivedData;
        int _x;
        int _y;

        void closeSocket();

        int setupSelect(fd_set *read_fds);

        void sendMessage();

        bool endsWithCRLF(const std::string& str);

        void parseMapSize(const std::string& response);
};
