/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** operators
*/

#include <raylib.h>


Color operator!(Color color)
{
    Color newColor;
    newColor.r = 255 - color.r;
    newColor.g = 255 - color.g;
    newColor.b = 255 - color.b;
    newColor.a = 255;

    return newColor;
}
