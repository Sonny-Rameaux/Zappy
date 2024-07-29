/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** zappy_server
*/

#ifndef ZAPPY_SERVER_H_
    #define ZAPPY_SERVER_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <ctype.h>
    #include <fcntl.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/select.h>
    #include <sys/wait.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <time.h>
    #include <stdarg.h>
    #include <signal.h>
    #define MAX_CLIENTS 10
    #define BUFFER_SIZE 1024
    #define LOWER 1024
    #define UPPER 65536
    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define UUID_LENGTH 255
    #define MAX_BODY_LENGTH 512

#endif /* !ZAPPY_SERVER_H_ */
