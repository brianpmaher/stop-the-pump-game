/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

// Ending Screen Initialization logic
void InitEndingScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxCoin);
    }
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLUE);

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    const char* gameOverText = "GAME OVER";
    const int fontSize = 40;
    const int gameOverTextWidth = MeasureText(gameOverText, fontSize);
    const int rowCount = 3;
    const int margin = 80;
    const int rowHeight = fontSize + margin;
    const Color color = WHITE;
    DrawText(gameOverText,
        // x position
        screenWidth / 2 - gameOverTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2,
        fontSize,
        color);
    const char* roundsText = TextFormat("Rounds Survived: %d", rounds);
    const int roundsTextWidth = MeasureText(roundsText, fontSize);
    DrawText(roundsText,
        // x position
        screenWidth / 2 - roundsTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + rowHeight,
        fontSize,
        color);
    const char* infoText = "Press ENTER to return to play again";
    const int infoTextWidth = MeasureText(infoText, fontSize);
    DrawText(infoText,
        // x position
        screenWidth / 2 - infoTextWidth / 2,
        // y position
        screenHeight / 2 - (rowCount * rowHeight) / 2 + 2 * rowHeight,
        fontSize,
        color);
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{
}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}
