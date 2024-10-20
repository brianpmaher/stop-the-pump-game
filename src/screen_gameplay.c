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
#include <math.h>

#define GO_TO_ENDING 0

static bool gameRunning;

static Camera camera;

static Model pumpModel;

static float currentPrice = 0.0f;
static float targetPrice = 0.0f;
static bool isPumping = false;
static float pumpSpeed = 0.1f;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------


void InitGameplayScreen(void)
{
    gameRunning = true;

    currentPrice = 0.0f;
    targetPrice = GetRandomValue(500, 5000) / 100.0f;
    isPumping = false;

    camera.position = (Vector3){10, 10, 10};
    camera.target = (Vector3){0, 0, 0};
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 10;
    camera.projection = CAMERA_ORTHOGRAPHIC;

    pumpModel = LoadModel("resources/pump.vox");
}

void UpdateGameplayScreen(void)
{
    if (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (!isPumping)
        {
            isPumping = true;
        }
        currentPrice += pumpSpeed;
    }
    else if (isPumping)
    {
        isPumping = false;
        if (fabsf(currentPrice - targetPrice) < 0.5f)
        {
            gameRunning = false;
        }
        else
        {
            // Reset for another try
            currentPrice = 0.0f;
            targetPrice = GetRandomValue(500, 5000) / 100.0f;
        }
    }
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

    DrawText("Gas Pump Game", 20, 20, 40, DARKGRAY);
    DrawText(TextFormat("Target: $%.2f", targetPrice), 20, 70, 30, DARKGREEN);
    DrawText(TextFormat("Current: $%.2f", currentPrice), 20, 110, 30, MAROON);

    // Draw pump instructions
    if (!isPumping)
    {
        DrawText("Hold SPACE or LEFT MOUSE BUTTON to pump", 20, GetScreenHeight() - 40, 20, DARKGRAY);
    }
    else
    {
        DrawText("Release to stop pumping", 20, GetScreenHeight() - 40, 20, DARKGRAY);
    }
}

void UnloadGameplayScreen(void)
{
}

int FinishGameplayScreen(void)
{
    return !gameRunning;
}
