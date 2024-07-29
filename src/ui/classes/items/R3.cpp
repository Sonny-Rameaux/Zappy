/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R3
*/

#include "../../../../include/ui/R3.hpp"

zap::R3::R3(Vector3 pos): _asset(pos, {0.15,0.5,0.15}, SKYBLUE)
{
}

void zap::R3::Draw()
{
    if (_onMap == true) {
        _asset.Draw();
    }
    
}

zap::R3::~R3()
{
}
