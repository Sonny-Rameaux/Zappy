/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Case
*/

#include "../../../../include/ui/Case.hpp"

zap::Case::Case(Vector3 pos, Color color) : _case(pos, color), _r1(pos), _r2(pos), _r3(pos), _r4(pos), _r5(pos), _r6(pos), _r7(pos)
{
    Vector3 resourcesPos = pos;
    resourcesPos.x-=1;
    resourcesPos.z-=1;
    resourcesPos.x+=0.25;
    resourcesPos.y+=+0.25;
    resourcesPos.z+=0.1;
    _r1 = zap::R1(resourcesPos);
    resourcesPos.x+=0.25;
    _r2 = zap::R2(resourcesPos);
    resourcesPos.x+=0.25;
    _r3 = zap::R3(resourcesPos);
    resourcesPos.x+=0.25;
    _r4 = zap::R4(resourcesPos);
    resourcesPos.x+=0.25;
    _r5 = zap::R5(resourcesPos);
    resourcesPos.x+=0.25;
    _r6 = zap::R6(resourcesPos);
    resourcesPos.x+=0.25;
    _r7 = zap::R7(resourcesPos);
    resourcesPos.x+=0.25;

}

void zap::Case::Update()
{
    _r1.Update(false);
    _r2.Update(false);
    _r3.Update(false);
    _r4.Update(false);
    _r5.Update(false);
    _r6.Update(false);
    _r7.Update(false);
    for (size_t i = 0; i < _inv._inv.size(); i++)
    {
        if (_inv._inv[i].get()->_name == "food") {
        _r1.Update(true);
        } if (_inv._inv[i].get()->_name == "linemate") {
        _r2.Update(true);
        } if (_inv._inv[i].get()->_name == "deraumere") {
        _r3.Update(true);
        } if (_inv._inv[i].get()->_name == "sibur") {
        _r4.Update(true);
        } if (_inv._inv[i].get()->_name == "mendiane") {
        _r5.Update(true);
        } if (_inv._inv[i].get()->_name == "phiras") {
        _r6.Update(true);
        } if (_inv._inv[i].get()->_name == "thystame") {
        _r7.Update(true);
        }
    }

}

void zap::Case::Draw()
{
    _r1.Draw();
    _r2.Draw();
    _r3.Draw();
    _r4.Draw();
    _r5.Draw();
    _r6.Draw();
    _r7.Draw();
    _case.Draw();
}

zap::Case::~Case()
{
}
