/*
** EPITECH PROJECT, 2024
** bs (2)
** File description:
** Cube
*/

#include "../../../../include/ui/Cube.hpp"

zap::Cube::Cube(Vector3 pos, Vector3 size, Color color)
{
    _pos = pos;
    _size = size;
    _color = color;
}

zap::Cube::Cube(Color color)
{
    _color = color;
}

zap::Cube::Cube(Vector3 pos, Color color)
{
    _pos = pos;
    _color = color;
}
void zap::Cube::setPos(Vector3 pos)
{
    _pos = pos;
}

Vector3 zap::Cube::getPos() { return _pos; };
Color zap::Cube::getColor() { return _color; };

void zap::Cube::Draw()
{
    DrawCube(_pos, _size.x, _size.y, _size.z, _color);
}
