/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

#include <ctime>

class Clock {
    public:
        Clock();
        ~Clock();

        double getValueInSeconds();
        void reset();

    protected:
    private:
        clock_t _clock;
};

#endif /* !CLOCK_HPP_ */
