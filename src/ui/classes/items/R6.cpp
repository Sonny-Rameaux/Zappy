/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R6
*/

#include "../../../../include/ui/R6.hpp"

zap::R6::R6(Vector3 pos): _asset(pos, {0.15,0.5,0.15}, YELLOW)
{
}

void zap::R6::Draw()
{
    if (_onMap == true) {
        _asset.Draw();
    }
    
}

zap::R6::~R6()
{
}
