/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R1
*/
#pragma once
#include "Cube.hpp"
#include <iostream>
#include "AResource.hpp"

namespace zap {
    class R1 : public AResource {
    public:
        R1(Vector3 pos);
        void Draw() override;
        void Update(bool newVal) override { _onMap = newVal; }  // Implémentation de Update
        ~R1() override;  // Déclaration du destructeur

    private:
        zap::Cube _asset;
        bool _onMap = false;
    };
} // namespace zap
