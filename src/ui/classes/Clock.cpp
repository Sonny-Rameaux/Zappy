/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Clock
*/

#include "../../../include/ui/Clock.hpp"

Clock::Clock() : _clock(std::clock())
{
}

Clock::~Clock()
{
}

double Clock::getValueInSeconds()
{
    return static_cast<double>(std::clock() - this->_clock) / CLOCKS_PER_SEC;
}

void Clock::reset()
{
    this->_clock = std::clock();
}
