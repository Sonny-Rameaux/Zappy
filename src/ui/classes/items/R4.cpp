/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R4
*/

#include "../../../../include/ui/R4.hpp"

zap::R4::R4(Vector3 pos) : _asset(pos, {0.15,0.5,0.15}, MAROON)
{
}

void zap::R4::Draw()
{
    if (_onMap == true) {
        _asset.Draw();
    }
    
}

zap::R4::~R4()
{
}
