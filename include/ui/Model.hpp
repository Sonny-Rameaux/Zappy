/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** PModel
*/

#pragma once
#include <raylib.h>
#include <rlgl.h>
#include "ADrawable.hpp"
namespace zap
{
    class PModel : public ADrawable {
        public:
            PModel(Vector3 _playerPosition, Color pColor);
            ~PModel();
            void setPos(Vector3 pos);
            void Draw() override;
            void Rotate();
            Color getPlayerColor() { return _playerColor; };
            float _angle =0;

        protected:
        private:
            Vector3 _position;
            Model _model;
            Texture2D _textures[3];
            Color _playerColor;
    };

    class EModel : public ADrawable {
    public:
        EModel(Vector3 _playerPosition);
        ~EModel();
        void setPos(Vector3 pos);
        void Draw() override;
        Vector3 _position;
    private:
            Model _model;
    };
} // namespace zap
