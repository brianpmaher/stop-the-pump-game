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
#include "raymath.h"

// TODO: Fade in text near animation end
// TODO: Game end state
// TODO: Music
// TODO: Title screen and game over screen

#define GO_TO_ENDING 0

static bool gameRunning;

static Camera camera;
// Camera animation
static const Vector3 cameraTarget = {0, 4.25, 0};
static const Vector3 cameraAnimationPosition1 = {50, 50, 50};
static const Vector3 cameraAnimationPosition2 = {0, 10, 15};
static const float cameraAnimationTime = 2;
static float cameraAnimationCurrentTime = 0;

static Model pumpModel;

static float currentPrice = 0.0f;
static float targetPrice = 0.0f;
static bool isPumping = false;
static float pumpSpeed = 0.015f;
static float score = 0;
static int rounds = 0;
static int priceRangeMinCents = 25;
static int priceRangeMaxCents = 200;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

static void UpdateGameCamera(float deltaTime)
{
    cameraAnimationCurrentTime += deltaTime;
    camera.position = Vector3Lerp(cameraAnimationPosition1, cameraAnimationPosition2, Clamp(cameraAnimationCurrentTime / cameraAnimationTime, 0, 1));
}

void InitGameplayScreen(void)
{
    gameRunning = true;

    currentPrice = 0.0f;
    targetPrice = GetRandomValue(priceRangeMinCents, priceRangeMaxCents) / 100.0f;
    isPumping = false;

    camera.position = cameraAnimationPosition1;
    camera.target = cameraTarget;
    camera.up = (Vector3){0, 1, 0};
    camera.fovy = 10;
    camera.projection = CAMERA_PERSPECTIVE;

    pumpModel = LoadModel("resources/pump.vox");

    currentPrice = 0.0f;
    isPumping = false;
    pumpSpeed = 0.15f * Clamp(rounds * 2 / 10.0f, 1.0f, 5.0f);
    score = 0;
    rounds = 0;
}

void UpdateGameplayScreen(void)
{
    const float deltaTime = GetFrameTime();

    if (IsKeyDown(KEY_SPACE) || IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if (!isPumping)
        {
            isPumping = true;
        }
        currentPrice = currentPrice + (pumpSpeed * deltaTime);
    }
    else if (isPumping)
    {
        isPumping = false;
        // Game over
        const float roundDelta = fabsf(currentPrice - targetPrice);
        if (roundDelta < 0.02f)
        {
            score -= 0.25f;
            if (score < 0.0f)
            {
                score = 0.0f;
            }
            PlaySound(fxCoin);
        }
        else 
        {
            PlaySound(fxError);
        }
        rounds += 1;

        score += roundDelta;
        const bool isEndGame = score > 1.0f;
        if (isEndGame)
        {
            gameRunning = false;
        }
        else
        {
            // Reset for another try
            currentPrice = 0.0f;
            targetPrice = GetRandomValue(priceRangeMinCents, priceRangeMaxCents) / 100.0f;
        }
    }

    // UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    UpdateGameCamera(deltaTime);
}

void DrawGameplayScreen(void)
{
    ClearBackground(BLACK);

    BeginMode3D(camera);
    {
        //DrawGrid(10, 1.0);

        DrawModel(pumpModel, (Vector3){-5.25, 0, -7}, 1.0, WHITE);

        const float cameraAnimationTargetScale = 1.0;
        const Color cameraAnimationTargetColor = MAROON;
        // DrawSphere(cameraAnimationPosition1, cameraAnimationTargetScale, cameraAnimationTargetColor);
        DrawSphere(cameraAnimationPosition2, cameraAnimationTargetScale, cameraAnimationTargetColor);
    }
    EndMode3D();

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const char* titleText = "Gas Pump Game";
    const int fontSize = 40;
    const int titleTextWidth = MeasureText(titleText, fontSize);
    const int rowCount = 4;
    const int margin = 80;
    const int rowHeight = fontSize + margin;
    DrawText(titleText,
        // x position
        screenWidth / 2 - titleTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2,
        fontSize,
        DARKGRAY);
    const char* targetText = TextFormat("Target: $%.2f", targetPrice);
    const int targetTextWidth = MeasureText(targetText, fontSize);
    DrawText(targetText,
        // x position
        screenWidth / 2 - targetTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + rowHeight,
        fontSize,
        DARKGRAY);
    const char* currentText = TextFormat("Current: $%.2f", currentPrice);
    const int currentTextWidth = MeasureText(currentText, fontSize);
    DrawText(currentText,
        // x position
        screenWidth / 2 - currentTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 2 * rowHeight,
        fontSize,
        DARKGRAY);
    const char* scoreText = TextFormat("Score: $%.2f", score);
    const int scoreTextWidth = MeasureText(scoreText, fontSize);
    DrawText(scoreText,
        // x position
        screenWidth / 2 - scoreTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 3 * rowHeight - 20,
        fontSize,
        DARKGRAY);
    const char* scoreLabelText = "Keep score below $1.00";
    const int scoreLabelFontSize = 20;
    const int scoreLabelTextWidth = MeasureText(scoreLabelText, scoreLabelFontSize);
    DrawText(scoreLabelText,
        // x position
        screenWidth / 2 - scoreLabelTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 4 * rowHeight - 100,
        scoreLabelFontSize,
        DARKGRAY);
    const char* scoreLabel2Text = "Below $0.02 reduces score by $0.25";
    const int scoreLabel2FontSize = 20;
    const int scoreLabel2TextWidth = MeasureText(scoreLabel2Text, scoreLabel2FontSize);
    DrawText(scoreLabel2Text,
        // x position
        screenWidth / 2 - scoreLabel2TextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 4 * rowHeight - 75,
        scoreLabel2FontSize,
        DARKGRAY);
    const char* scoreLabel3Text = "Lower score is better";
    const int scoreLabel3FontSize = 20;
    const int scoreLabel3TextWidth = MeasureText(scoreLabel3Text, scoreLabel3FontSize);
    DrawText(scoreLabel3Text,
        // x position
        screenWidth / 2 - scoreLabel3TextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 4 * rowHeight - 50,
        scoreLabel3FontSize,
        DARKGRAY);
    const char* roundsText = TextFormat("Rounds: %d", rounds);
    const int roundsTextWidth = MeasureText(roundsText, fontSize);
    DrawText(roundsText,
        // x position
        screenWidth / 2 - roundsTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 5 * rowHeight - 150,
        fontSize,
        DARKGRAY);

    // Draw pump instructions
    if (!isPumping)
    {
        DrawText("Hold SPACE or LEFT MOUSE BUTTON to pump", 20, GetScreenHeight() - 40, 20, WHITE);
    }
    else
    {
        DrawText("Release to stop pumping", 20, GetScreenHeight() - 40, 20, WHITE);
    }
}

void UnloadGameplayScreen(void)
{
}

int FinishGameplayScreen(void)
{
    return !gameRunning;
}
