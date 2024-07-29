/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** IDrawable
*/

#pragma once

class IDrawable {
    public:
        virtual ~IDrawable() = default;
        virtual void Draw() = 0;
    protected:
    private:
};
