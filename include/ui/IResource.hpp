/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** IResource
*/
#pragma once

class IResource {
public:
    virtual void Draw() = 0;  // Méthode purement virtuelle
    virtual void Update(bool newVal) = 0;  // Méthode purement virtuelle
    // virtual ~IResource() = default;
};
