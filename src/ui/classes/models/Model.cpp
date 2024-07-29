/*
** EPITECH PROJECT, 2024
** B-YEP-400-MAR-4-1-zappy-vincent.montero-fontaine
** File description:
** Model
*/

#include "../../../../include/ui/Model.hpp"
#include <raylib.h>

zap::PModel::PModel(Vector3 playerPosition, Color pColor)
{
    _model = LoadModel("eevee/scene.gltf");
    _textures[1] = LoadTexture("eevee/textures/Material_12_baseColor.png");
    _textures[2] = LoadTexture("eevee/textures/Material_13_baseColor.png");
    _textures[0] = LoadTexture("eevee/textures/Material_14_baseColor.png");

    for (int i = 0; i < _model.materialCount; i++)
    {
        _model.materials[i].maps[MATERIAL_MAP_DIFFUSE].texture = _textures[i];
    }

    _position = playerPosition;
    _playerColor = pColor;

}

void zap::PModel::setPos(Vector3 pos){
    _position = pos;
}



void zap::PModel::Draw()
{
    DrawModelEx(_model, _position, {0, 1, 0}, _angle,{0.05, 0.05, 0.05}, _playerColor);
    // DrawModel(_model, _position, 0.05f, _playerColor);
}

zap::PModel::~PModel()
{
    UnloadModel(_model);
    // for (int i = 0; i < 3; i++) UnloadTexture(_textures[i]);
}


namespace zap
{
    EModel::EModel(Vector3 playerPosition)
    {
        _model = LoadModel("egg/10858_egg_v2_L3.obj");
        _position = playerPosition;

        if (!_model.meshes || !_model.materials) {
            std::cerr << "Failed to load model: egg/10858_egg_v2_L3.obj" << std::endl;
            return;
        }
    }

    void EModel::setPos(Vector3 pos)
    {
        _position = pos;
    }

    void EModel::Draw()
    {
        rlPushMatrix();
        rlTranslatef(_position.x, _position.y, _position.z); // Translation vers la position du modèle
        rlRotatef(-90, 1.0f, 0.0f, 0.0f); // Rotation autour de l'axe Y
        rlScalef(0.4f, 0.4f, 0.4f); // Appliquer l'échelle
        DrawModel(_model, {0, 0, 0}, 1.0f, WHITE); // Dessiner le modèle à l'origine
        rlPopMatrix();
    }

    EModel::~EModel()
    {
        UnloadModel(_model);
    }
} // namespace zap
