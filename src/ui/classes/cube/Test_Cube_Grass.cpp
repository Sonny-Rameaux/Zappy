#include "raylib.h"
#include "rlgl.h"
#include <iostream>

// Fonction pour dessiner un brin d'herbe à une position donnée
void DrawSingleGrassBlade(Vector3 position, Texture2D grassBladeTexture, float bladeHeight = 1.0f)
{
    // Calculer la largeur du brin d'herbe en fonction de sa hauteur et des dimensions de la texture
    float bladeWidth = grassBladeTexture.width * bladeHeight / grassBladeTexture.height;

    rlPushMatrix();
        rlTranslatef(position.x, position.y, position.z);
        rlScalef(bladeWidth, bladeHeight, 1.0f);

        rlBegin(RL_QUADS);
            rlSetTexture(grassBladeTexture.id);
            rlColor4ub(255, 255, 255, 255);

            rlTexCoord2f(0.0f, 1.0f); rlVertex3f(-0.5f, 0.0f, 0.0f);
            rlTexCoord2f(1.0f, 1.0f); rlVertex3f(0.5f, 0.0f, 0.0f);
            rlTexCoord2f(1.0f, 0.0f); rlVertex3f(0.5f, 1.0f, 0.0f);
            rlTexCoord2f(0.0f, 0.0f); rlVertex3f(-0.5f, 1.0f, 0.0f);

        rlEnd();
        rlSetTexture(0);
    rlPopMatrix();
}

// Fonction pour dessiner des brins d'herbe autour d'une position donnée
void DrawGrassBlades(Vector3 position, Texture2D grassBladeTexture, float bladeHeight = 1.0f)
{
    float offsets[4][2] = {
        {-0.5f, 0.5f},  // gauche
        {0.5f, 0.5f},   // droite
        {0.0f, 0.5f},   // centre
        {0.0f, -0.5f}   // arrière
    };

    for (int i = 0; i < 4; i++)
    {
        Vector3 bladePosition = { position.x + offsets[i][0], position.y, position.z + offsets[i][1] };
        DrawSingleGrassBlade(bladePosition, grassBladeTexture, bladeHeight);
    }
}

int main()
{
    // Initialiser la fenêtre
    InitWindow(800, 600, "Cube d'herbe 3D avec des brins d'herbe");

    // Initialiser la caméra
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 2.0f, 6.0f };
    camera.target = (Vector3){ 0.0f, 0.5f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    // Charger les textures
    Texture2D cubeTexture = LoadTexture("src/ui/classes/cube/grass_cube.png");
    Texture2D grassBladeTexture = LoadTexture("src/ui/classes/cube/grass_blade.png");

    SetTargetFPS(60);

    // Créer un modèle 3D avec une texture
    Model model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));

    // Appliquer la texture au modèle
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = cubeTexture;

    // Boucle principale
    while (!WindowShouldClose())
    {
        // Mise à jour de la caméra
        UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        // Dessiner le modèle 3D avec la texture d'herbe
        Vector3 cubePosition = { 0.0f, 0.5f, 0.0f };
        DrawModel(model, cubePosition, 1.0f, WHITE);

        // Dessiner les brins d'herbe
        DrawGrassBlades(cubePosition, grassBladeTexture);

        EndMode3D();

        DrawText("Cube d'herbe 3D avec des brins d'herbe", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    // Décharger les textures
    UnloadTexture(cubeTexture);
    UnloadTexture(grassBladeTexture);

    // Fermer la fenêtre
    CloseWindow();

    return 0;
}
