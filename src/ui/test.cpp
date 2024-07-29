/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** main
*/
#include <iostream>
#include <raylib.h>
#include <unistd.h>
#include "../../include/ui/Board.hpp"
#include "../../include/ui/Camera.hpp"
#include "../../include/ui/Cube.hpp"
#include "../../include/ui/Model.hpp"
#include "../../include/ui/Window.hpp"
#include "../../include/ui/ServerConnection.hpp"




int main(int argc, char **argv)
{
    int port;
    std::string machineName;

    if (argc != 5) {
        return 84;
    }
    if (std::string(argv[1]) == "-p" && std::string(argv[3]) == "-h") {
        port = atoi(argv[2]);
        machineName = std::string(argv[4]);
    } else {}

    zap::Window window;
    zap::ServerConnection(port, machineName.c_str());
    int x = 0;
    int z = 0;
    zap::Camera camera = zap::Camera();
    zap::Board board = zap::Board(4,4, 1);
    Vector3 pos = board.getPos(z, x);
    zap::PModel eevee = zap::PModel(pos, GREEN);
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_DOWN)){
            if (z < board.z()-1) z++;
        }
        if (IsKeyPressed(KEY_UP)){
            if (z > 0) z--;
        }
        if (IsKeyPressed(KEY_RIGHT)){
            if (x < board.x()-1) x++;
        }
        if (IsKeyPressed(KEY_LEFT)){
            if (x > 0) x--;
        }
        pos = board.getPos(z, x);
        pos.y += 1;
        eevee.setPos(pos);

        camera.APressed();
        camera.DPressed();
        camera.SPressed();
        camera.WPressed();
        BeginDrawing();
            BeginMode3D(camera.getCam());
            ClearBackground(BLUE);
                board.Draw();
                eevee.Draw();
            EndMode3D();
            DrawFPS(10, 10);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    CloseWindow();
    return 0;
}