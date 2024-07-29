/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** MenuCase
*/

#ifndef MENUCASE_HPP_
#define MENUCASE_HPP_

#include <raylib.h>
#include <vector>
#include "../../include/ui/Board.hpp"

namespace zap {
    class MenuCase
    {
        public:
            MenuCase(Texture2D texture, Vector2 position, Board &board);
            ~MenuCase();
            void Draw();
            void Update();

            void setSelect(float x, float z);
            void setAncienCube(float x, float z);
            Vector2 getSelect() { return select; };
            Texture2D getTexture() { return menuTexture; };
            int getTotalQuantity(std::string name);
            Color ancienCube;
            Vector2 ancienPosition;

        private:
            bool show = true;
            Vector2 select;
            Texture2D menuTexture;
            Vector2 menuPosition;
            std::vector<Texture2D> icone;
            Board &info;
    };
}

#endif /* !MENUCASE_HPP_ */
