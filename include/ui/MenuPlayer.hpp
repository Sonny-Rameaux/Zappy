/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** MenuPlayer
*/

#ifndef MENUPLAYER_HPP_
#define MENUPLAYER_HPP_

#include <raylib.h>
#include <vector>
#include "../../include/ui/Board.hpp"

namespace zap {
    class MenuPlayer
    {
        public:
            MenuPlayer(Texture2D texture, Vector2 position, Board &board);
            ~MenuPlayer();
            void Draw();
            void Update(int key);

            Texture2D getTexture() { return menuTexture; };

            int idTeam;
            int idPlayer;
        private:
            bool show = true;
            Texture2D menuTexture;
            Vector2 menuPosition;
            std::vector<Texture2D> icone;
            Board &info;
    };
}

#endif /* !MENUPLAYER_HPP_ */
