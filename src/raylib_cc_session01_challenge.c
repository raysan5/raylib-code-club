/*******************************************************************************************
*
*   raylib CODE CLUB - Session 01
*
*   CHALLENGE: PONG
*     - Only gameplay screen
*     - One ball bouncing on screen
*     - Two players: 
*         - Players can not go out of screen limits
*         - Player 1 controlled with inputs: UP/DOWN
*         - Player 2 controlled by simple AI
*     - Game pause system
*     - Scoring system, displayed on screen (Player/AI)
*     - Game time, displayed on screen
*     - EXTRA: Four Screens: LOGO, TITLE, GAMEPLAY, ENDING
*
*   Code licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
********************************************************************************************/

#include "raylib.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib CODE CLUB - Session 01 - PONG");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Welcome to raylib CODE CLUB", 180, 200, 30, MAROON);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}