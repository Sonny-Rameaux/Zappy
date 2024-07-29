#include "../../../include/ui/connection.hpp"
#include <cstddef>

TCPClient::TCPClient(const char *ip, const char *port) : server_ip(ip), server_port(port), client_socket(-1) {}

TCPClient::~TCPClient() {
    closeSocket();
}

bool TCPClient::connectToServer() {
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        std::cerr << "Socket creation failed" << std::endl;
        return false;
    }

    int flags = fcntl(client_socket, F_GETFL, 0);
    fcntl(client_socket, F_SETFL, flags | O_NONBLOCK);

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr(server_ip);
    server_address.sin_port = htons(std::atoi(server_port));

    int result = connect(client_socket, reinterpret_cast<struct sockaddr *>(&server_address), sizeof(server_address));
    if (result == -1 && errno != EINPROGRESS) {
        std::cerr << "Connection failed" << std::endl;
        closeSocket();
        return false;
    }

    if (result == 0) {
        std::cout << "Connected to server immediately" << std::endl;
        return true;
    }

    fd_set write_fds;
    FD_ZERO(&write_fds);
    FD_SET(client_socket, &write_fds);

    result = select(client_socket + 1, NULL, &write_fds, NULL, NULL);
    if (result == -1) {
        std::cerr << "Select error" << std::endl;
        closeSocket();
        return false;
    } else if (result == 0) {
        std::cerr << "Connection timed out" << std::endl;
        closeSocket();
        return false;
    } else {
        int optval;
        socklen_t optlen = sizeof(optval);
        if (getsockopt(client_socket, SOL_SOCKET, SO_ERROR, &optval, &optlen) == -1) {
            std::cerr << "Getsockopt error" << std::endl;
            closeSocket();
            return false;
        }
        if (optval != 0) {
            std::cerr << "Connection error: " << strerror(optval) << std::endl;
            closeSocket();
            return false;
        }
    }

    std::cout << "Connected to server" << std::endl;
    return true;
}

void TCPClient::startCommunication() {
    fd_set read_fds;
    if (setupSelect(&read_fds) == -1) {
        exit(0);
    }
    if (FD_ISSET(client_socket, &read_fds)) {
        handleServerResponse();
    }
}

void TCPClient::closeSocket() {
    if (client_socket != -1) {
        close(client_socket);
        client_socket = -1;
    }
}

int TCPClient::setupSelect(fd_set *read_fds) {
    FD_ZERO(read_fds);
    FD_SET(STDIN_FILENO, read_fds);
    FD_SET(client_socket, read_fds);
    int max_fd = (STDIN_FILENO > client_socket) ? STDIN_FILENO : client_socket;
    if (select(max_fd + 1, read_fds, nullptr, nullptr, nullptr) == -1) {
        std::cerr << "Select error" << std::endl;
        return -1;
    }
    return max_fd + 1;
}

void TCPClient::handleServerResponse() {
    char buffer[BUFFER_SIZE];
    this->receivedData.clear();

    while (true) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                return;
            } else {
                perror("Receive failed");
                closeSocket();
                connected = false;
                return;
            }
        } else if (bytes_received == 0) {
            std::cerr << "Server disconnected" << std::endl;
            closeSocket();
            connected = false;
            return;
        }
        buffer[bytes_received] = '\0';
        this->receivedData.append(buffer);
        // boost::erase_all(this->receivedData, "\r\n");
        if (this->receivedData.size() >= 2 &&
            this->receivedData.compare(this->receivedData.size() - 2, 2, "\r\n") == 0) {
            break;
        }
    }
}


void TCPClient::sendMessage() {
    char message[BUFFER_SIZE];
    if (!fgets(message, sizeof(message), stdin)) {
        std::cerr << "Error reading from stdin" << std::endl;
        return;
    }
    message[strcspn(message, "\n")] = '\0';
    strcat(message, "\r\n");
    if (send(client_socket, message, strlen(message), 0) == -1) {
        perror("Send failed");
        closeSocket();
        throw std::runtime_error("Couldn't send message");
    }
}

void TCPClient::sendStaticMessage(const std::string& msg) {
    std::string message = msg + "\r\n";
    if (send(client_socket, message.c_str(), message.length(), 0) == -1) {
        closeSocket();
        throw std::runtime_error("Connection closed by server");
    }
}

bool TCPClient::endsWithCRLF(const std::string& str) {
    std::size_t len = str.length();
    return (len >= 2 && str[len - 2] == '\r' && str[len - 1] == '\n');
}

void TCPClient::handleInitialServerResponse() {
    char buffer[BUFFER_SIZE];
    std::string received_message;
    int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received <= 0) {
        if (bytes_received == 0) {
            std::cerr << "Server disconnected" << std::endl;
        } else {
            perror("Receive failed");
        }
        closeSocket();
        throw std::runtime_error("Couldn't receive initial response");
    }
    buffer[bytes_received] = '\0';
    received_message.append(buffer);
    parseMapSize(received_message);
}

void TCPClient::parseMapSize(const std::string& response) {
    std::istringstream iss(response);
    if (!(iss >> _x >> _y)) {
        std::cerr << "Failed to parse map size from server response" << std::endl;
        closeSocket();
        throw std::runtime_error("Couldn't parse map size");
    }
}

void TCPClient::receiveWelcomeMessage() {
    char buffer[BUFFER_SIZE];
    std::string received_message;

    while (true) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            } else {
                perror("Receive failed");
                closeSocket();
                throw std::runtime_error("Receive failed");
            }
        } else if (bytes_received == 0) {
            std::cerr << "Server disconnected" << std::endl;
            closeSocket();
            throw std::runtime_error("Server disconnected");
        }

        buffer[bytes_received] = '\0';
        received_message.append(buffer);

        if (received_message.size() >= 2 &&
            received_message.compare(received_message.size() - 2, 2, "\r\n") == 0) {
            break;
        }
    }
    std::cout << "Welcome message received: " << received_message << std::endl;
}

void TCPClient::receiveAndParseMapSize() {
    char buffer[BUFFER_SIZE];
    std::string received_message;

    while (true) {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

        if (bytes_received < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                continue;
            } else {
                perror("Receive failed");
                closeSocket();
                throw std::runtime_error("Receive failed");
            }
        } else if (bytes_received == 0) {
            std::cerr << "Server disconnected" << std::endl;
            closeSocket();
            throw std::runtime_error("Server disconnected");
        }

        buffer[bytes_received] = '\0';
        received_message.append(buffer);

        if (received_message.size() >= 2 &&
            received_message.compare(received_message.size() - 2, 2, "\r\n") == 0) {
            break;  // Received complete message
        }
    }
    std::istringstream iss(received_message);
    if (!(iss >> _x >> _y)) {
        std::cerr << "Failed to parse map size from server response" << std::endl;
        closeSocket();
        throw std::runtime_error("Couldn't parse map size");
    }

    std::cout << "Map size received: x = " << _x << ", y = " << _y << std::endl;
}

/* MCT */
std::string TCPClient::getReceivedData() const {
    return receivedData;
}

void TCPClient::clearReceivedData() {
    receivedData.clear();
}

void TCPClient::parseMCTResponse(const std::string& response) {
    std::istringstream iss(response);
    std::string currentLine;
    bool isLastLine = false;

    _tiles.clear();
    while (std::getline(iss, currentLine, '\n')) {
        if (endsWithCRLF(currentLine)) {
            isLastLine = true;
            currentLine.erase(currentLine.size() - 2);
        }

        if (currentLine.empty()) {
            continue;
        }

        std::istringstream line_stream(currentLine);
        std::string component;
        std::string items;

        // for (int i = 0; i < 3; ++i) {
        //     if (!(line_stream >> component)) {
        //         throw std::runtime_error("Error parsing line: " + currentLine);
        //     }
        // }

        while (line_stream >> component) {
            items += component;
        }

        _tiles.push_back(items);

        if (isLastLine) {
            break;
        }
    }
}

void TCPClient::printTiles() const
{
    std::cout << "-------------------------------" << std::endl;
    for (const auto& tile : _tiles) {
        std::cout << tile << std::endl;
    }
    std::cout << "-------------------------------" << std::endl;
}
