/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Case
*/

#pragma once
#include "Cube.hpp"
#include <iostream>
#include <vector>
#include "R1.hpp"
#include "R2.hpp"
#include "R3.hpp"
#include "R4.hpp"
#include "R5.hpp"
#include "R6.hpp"
#include "R7.hpp"

namespace zap
{
    class Case : public ADrawable {
        public:
            Case(Vector3 pos, Color color);
            void Draw() override;
            void Update();
            Vector3 getPos(){return _case.getPos();};
            ~Case();
            Inventory _inv;
            Cube _case;
        protected:
        private:
        R1 _r1;
        R2 _r2;
        R3 _r3;
        R4 _r4;
        R5 _r5;
        R6 _r6;
        R7 _r7;

    };
} // namespace zap
