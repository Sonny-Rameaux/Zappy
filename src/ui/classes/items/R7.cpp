/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R7
*/

#include "../../../../include/ui/R7.hpp"

zap::R7::R7(Vector3 pos): _asset(pos, {0.15,0.5,0.15}, GOLD)
{
}

void zap::R7::Draw()
{
    if (_onMap == true) {
        _asset.Draw();
    }
    
}

zap::R7::~R7()
{
}
