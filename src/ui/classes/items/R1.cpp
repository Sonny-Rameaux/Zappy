/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** R1
*/
#include "../../../../include/ui/R1.hpp"

zap::R1::R1(Vector3 pos) : _asset(pos, {0.15, 0.5, 0.15}, RED) {
    // Initialisation ou autre code si nécessaire
}

void zap::R1::Draw() {
    if (_onMap) {
        _asset.Draw();
    }
}

zap::R1::~R1() {
    // Nettoyage ou autre code si nécessaire
}
