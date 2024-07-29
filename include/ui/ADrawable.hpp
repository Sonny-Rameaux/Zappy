/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** ADrawable
*/

#pragma once    
#include "IDrawable.hpp"
#include <iostream>

class ADrawable : public IDrawable {
    public:
        ADrawable(){}
        virtual void Draw() override{}
        ~ADrawable(){}

    protected:
    private:
};
