/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

#define GO_TO_ENDING 0

static bool gameRunning;

static Camera camera;

static Model pumpModel;

void InitGameplayScreen(void)
{
    gameRunning = true;

    camera.position = (Vector3){10, 10, 10};
    camera.target = (Vector3){0, 0, 0};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 10;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    pumpModel = LoadModel("resources/pump.vox");
}

void UpdateGameplayScreen(void)
{
    UpdateCamera(&camera, CAMERA_ORBITAL);
}

void DrawGameplayScreen(void)
{
    BeginMode3D(camera);
    {
        DrawGrid(10, 1.0);
        DrawModel(pumpModel, (Vector3){0, 0, 0}, 1.0, WHITE);
    }
    EndMode3D();
}

void UnloadGameplayScreen(void)
{
}

int FinishGameplayScreen(void)
{
    return !gameRunning;
}
