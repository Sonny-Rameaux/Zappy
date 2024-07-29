/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R2
*/

#include "../../../../include/ui/R2.hpp"

zap::R2::R2(Vector3 pos): _asset(pos, {0.15,0.5,0.15}, MAGENTA)
{
}

void zap::R2::Draw()
{
    if (_onMap == true) {
        _asset.Draw();
    }
    
}

zap::R2::~R2()
{
}
