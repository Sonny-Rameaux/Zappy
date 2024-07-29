/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** AResource
*/
#pragma once
#include "IResource.hpp"

class AResource : public IResource {
public:
    AResource() = default;
    virtual void Draw() override {};  // Implémentation par défaut (vide)
    virtual void Update(bool newVal) override {};  // Implémentation par défaut (vide)
    virtual ~AResource() = default;
};
