/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** Cube
*/

#pragma once
#include <raylib.h>
#include "ADrawable.hpp"
#include "Inventory.hpp"

namespace zap
{
    class Cube : public ADrawable {
        public:
            Cube() = default;
            Cube(Vector3 pos, Vector3 size, Color color);
            Cube(Color color);
            Cube(Vector3 pos,Color color);
            ~Cube() = default;
            void Draw() override;
            void setPos(Vector3 pos);
            Vector3 getPos();
            void setColor(Color newColor) { _color = newColor; };
            Color getColor();

        protected:
        private:
            Vector3 _pos = { 0.0f, 0.0f, 0.0f };
            Vector3 _size = { 2.0f, 0.2f, 2.0f };
            Color _color = BLACK;
    };
} // namespace zap
