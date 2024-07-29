/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Window
*/

#pragma once
#include <raylib.h>
#include <vector>
#include "ADrawable.hpp"
#include "IDrawable.hpp"

namespace zap
{
    class Window {
        public:
            Window();
            ~Window();

        protected:
        private:
            int _screenWidth = GetMonitorWidth(0)*0.8;
            int _screenHeight = GetMonitorHeight(0)*0.8;
    };
} // namespace zap

