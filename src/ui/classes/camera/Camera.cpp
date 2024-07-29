/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** Camera
*/

#include "../../../../include/ui/Camera.hpp"

zap::Camera::Camera(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection)
{
    camera.fovy = fovy;
    camera.position = position;
    camera.projection = projection;
    camera.target = target;
    camera.up = up;
}


void zap::Camera::APressed()
{
if (IsKeyDown(KEY_A))
    camera.position.x += 0.2f;
}

void zap::Camera::DPressed()
{
    if (IsKeyDown(KEY_D))
        camera.position.x -= 0.2f;
}

void zap::Camera::WPressed()
{
    if (IsKeyDown(KEY_W))
        camera.position.z -= 0.2f;
}

void zap::Camera::SPressed(){
    if (IsKeyDown(KEY_S))
        camera.position.z += 0.2f;
}
