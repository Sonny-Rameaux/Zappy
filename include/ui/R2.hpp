/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R2
*/

#pragma once
#include "Cube.hpp"
#include "AResource.hpp"
#include <iostream>
namespace zap
{
    class R2 : public AResource {
        public:
            R2(Vector3 pos);

            void Draw() override;
            void Update(bool newVal) override {_onMap = newVal;}
            ~R2();

        protected:
        private:
        zap::Cube _asset;
        bool _onMap = false;
        
    };
} // namespace zap

