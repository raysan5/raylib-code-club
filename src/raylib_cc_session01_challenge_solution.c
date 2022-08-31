/*******************************************************************************************
*
*   raylib CODE CLUB - Session 01
*
*   CHALLENGE: PONG
*     - Only gameplay screen
*     - Two players: 
*         - Player 1 controlled with inputs: UP/DOWN
*         - Player 2 controlled by simple AI
*     - Game pause
*     - Scoring system, displayed on screen
*     - Game time, displayed on screen
*
*   Code licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022 Ramon Santamaria (@raysan5)
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
    
    Vector2 ballPosition = { screenWidth/2.0f, screenHeight/2.0f };
    Vector2 ballSpeed = { 6.0f, 4.0f };
    float ballRadius = 10.0f;
    
    Rectangle player = { 10, screenHeight/2 - 50, 20, 100 };
    float playerSpeed = 18.0f;
    int playerScore = 0;
    
    Rectangle ai = { screenWidth - 30, screenHeight/2 - 60, 20, 120 };
    float aiSpeed = 5.0f;
    float aiVisionRange = 200;      // Vision range in pixels to start moving
    int aiScore = 0;
    
    bool pause = false;
    int frameCounter = 0;           // Used to count time (using frames)
    int blinkCounter = 0;           // Used for pause text blinking
    int scoreCooldown = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyPressed(KEY_P)) pause = !pause;
        
        if (!pause)
        {
            frameCounter++;
            
            // Ball movement logic
            ballPosition.x += ballSpeed.x;
            ballPosition.y += ballSpeed.y;
            
            if (((ballPosition.x + ballRadius) > GetScreenWidth()) || ((ballPosition.x - ballRadius) < 0)) ballSpeed.x *= -1.0f;
            if (((ballPosition.y + ballRadius) > GetScreenHeight()) || ((ballPosition.y - ballRadius) < 0)) ballSpeed.y *= -1.0f;
            
            // Player movement logic
            if (IsKeyDown(KEY_UP)) player.y -= playerSpeed;
            else if (IsKeyDown(KEY_DOWN)) player.y += playerSpeed;
            
            if (player.y < 0) player.y = 0;
            else if ((player.y + player.height) > GetScreenHeight()) player.y = GetScreenHeight() - player.height;
            
            // AI movement logic
            // Paddle starts moving when ball enters in vision range
            if (ballPosition.x > (GetRenderWidth() - aiVisionRange - 20))
            {
                // Try to chase ball position when in vision range
                if (ballPosition.y > (ai.y + ai.height/2)) ai.y += aiSpeed;
                if (ballPosition.y < (ai.y + ai.height/2)) ai.y -= aiSpeed;
                
                // Review screen limits
                if (ai.y < 0) ai.y = 0;
                else if ((ai.y + ai.height) > GetScreenHeight()) ai.y = GetScreenHeight() - ai.height;
            }
            
            // DEBUG: Adjust ai vision range
            if (IsKeyDown(KEY_RIGHT)) aiVisionRange--;
            else if (IsKeyDown(KEY_LEFT)) aiVisionRange++;
            
            // Player-ball collision logic
            if (CheckCollisionCircleRec(ballPosition, ballRadius, player)) ballSpeed.x *= -1;
            
            // AI-ball collision logic
            if (CheckCollisionCircleRec(ballPosition, ballRadius, ai)) ballSpeed.x *= -1;
            
            // Scoring system, check ball limits with cooldown
            if (scoreCooldown <= 0)
            {
                if ((ballPosition.x - ballRadius) <= 0) 
                {
                    playerScore++;
                    scoreCooldown = 60;
                }
                else if ((ballPosition.x + ballRadius) >= GetScreenWidth()) 
                {
                    aiScore++;
                    scoreCooldown = 60;
                }
            }
            else scoreCooldown--;
        }
        else blinkCounter++;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            // Draw ball and players
            DrawCircleV(ballPosition, ballRadius, MAROON);
            DrawRectangleRec(player, LIME);
            DrawRectangleRec(ai, DARKBLUE);
            
            // DEBUG: Draw ai vision range line
            DrawLine(GetScreenWidth() - aiVisionRange - 20, 0, GetScreenWidth() - aiVisionRange - 20, GetScreenHeight(), LIGHTGRAY);
            
            // Draw score
            DrawText(TextFormat("%02i : %02i", playerScore, aiScore), 320, 10, 50, GRAY);
            
            // Draw time
            DrawText(TextFormat("%02i : %02i : %02i", frameCounter/3600, (frameCounter/60)%60, frameCounter%60), 320, GetScreenHeight() - 40, 30, RED);
            
            // Draw pause text with text blinking
            if (pause && ((blinkCounter/30)%2 == 0)) DrawText("GAME PAUSED", 300, 160, 30, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}