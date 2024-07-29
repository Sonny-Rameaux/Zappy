/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** Camera
*/

#pragma once
#include <raylib.h>
namespace zap
{
    class Camera {
        public:
            Camera(Vector3 position, Vector3 target, Vector3 up, float fovy, int projection);
            Camera() = default;
            ~Camera() = default;
            void APressed();
            void DPressed();
            void WPressed();
            void SPressed();
            void setTarget(Vector3 newTarget) { camera.target = newTarget; };
            void setPosition(Vector3 newPosition) { camera.position = newPosition; };
            Camera3D getCam(){return camera;}

        protected:
        private:
        Camera3D camera = { { 0.0f, 10.0f, 35.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE };

    };

}
