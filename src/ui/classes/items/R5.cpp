/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R5
*/

#include "../../../../include/ui/R5.hpp"

zap::R5::R5(Vector3 pos): _asset(pos, {0.15,0.5,0.15}, GREEN)
{
}

void zap::R5::Draw()
{
    if (_onMap == true) {
        _asset.Draw();
    }
    
}

zap::R5::~R5()
{
}
