/*******************************************************************************************
*
*   raylib CODE CLUB - Session 02
*
*   CHALLENGE: SHAPE SELECTOR
*     - Choose a shape: TRIANGLE, RECTANGLE, CIRCLE, POLY
*     - Keyboard shape selectors: KEY_LEFT-KEY_RIGHT
*     - Background grid for the shapes
*     - Lines or Fill mode toggle: KEY_L
*     - Random color selection: KEY_SPACE
*     - Usage instructions and state written on screen
*     - EXTRA: Random selection mode (every 0.2 seconds)
*
*   Code licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
********************************************************************************************/

#include "raylib.h"

typedef enum {
   SHAPE_TRIANGLE = 0,
   SHAPE_RECTANGLE,
   SHAPE_CIRCLE,
   SHAPE_POLY
} ShapeType; 

const char *shapeTypeName[4] = { "TRIANGLE", "RECTANGLE", "CIRCLE", "POLY" };   

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib CODE CLUB - Session 02 - SHAPE SELECTOR");
    
    int currentShape = SHAPE_CIRCLE;
    Color color = RED; 
    bool linesMode = false;
    
    bool randomMode = false;
    int framesCounter = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Select current shape to draw
        if (IsKeyPressed(KEY_RIGHT)) currentShape++;
        else if (IsKeyPressed(KEY_LEFT)) currentShape--;
        
        if (currentShape < 0) currentShape = 3;
        else if (currentShape > 3) currentShape = 0;
        
        // Toogle lines drawing mode
        if (IsKeyPressed(KEY_L)) linesMode = !linesMode;
        
        // Random color selector
        if (IsKeyPressed(KEY_SPACE))
        {
            color.r = (unsigned char)GetRandomValue(40, 220);
            color.g = (unsigned char)GetRandomValue(40, 220);
            color.b = (unsigned char)GetRandomValue(40, 220);
            color.a = 255;
        }
        
        // Enable random mode
        if (IsKeyPressed(KEY_R)) randomMode = !randomMode;
        
        if (randomMode)
        {
            framesCounter++;
            
            if (framesCounter >= 12)
            {
                currentShape = GetRandomValue(0, 3);
                linesMode = GetRandomValue(0, 1);
                color.r = (unsigned char)GetRandomValue(40, 220);
                color.g = (unsigned char)GetRandomValue(40, 220);
                color.b = (unsigned char)GetRandomValue(40, 220);
                color.a = 255;
                
                framesCounter = 0;
            }
        }
        else framesCounter = 0;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // Draw 2d grid for convenience
            for (int y = 0; y < 14; y++) DrawLine(200, 140 + 20*y, 200 + 400, 140 + 20*y, LIGHTGRAY);
            for (int x = 0; x < 21; x++) DrawLine(200 + 20*x, 140, 200 + 20*x, 140 + 260, LIGHTGRAY);

            // Draw current selected shape
            switch (currentShape)
            {
                case SHAPE_TRIANGLE: 
                {
                    if (linesMode) DrawTriangleLines((Vector2){ 400, 200 }, (Vector2){ 300, 340 }, (Vector2){ 500, 340 }, color);
                    else DrawTriangle((Vector2){ 400, 200 }, (Vector2){ 300, 340 }, (Vector2){ 500, 340 }, color);
                    
                } break;
                case SHAPE_RECTANGLE: 
                {
                    if (linesMode) DrawRectangleLines(300, 200, 200, 120, color);
                    else DrawRectangle(300, 200, 200, 120, color);
                    
                } break;
                case SHAPE_CIRCLE: 
                {
                    if (linesMode) DrawCircleLines(400, 270, 80, color);
                    else DrawCircle(400, 270, 80, color);
                    
                } break;
                case SHAPE_POLY: 
                {
                    if (linesMode) DrawPolyLines((Vector2){ 400, 270 }, 5, 80, 0.0f, color);
                    else DrawPoly((Vector2){ 400, 270 }, 5, 80, 0.0f, color);
                    
                } break;
                default: break;
            }
            
            DrawText(TextFormat("- [KEY_LEFT/KEY_RIGHT] Current shape: %s", shapeTypeName[currentShape]), 10, 10, 20, GRAY);
            DrawText(TextFormat("- [KEY_L] Lines drawing mode: %s", linesMode? "ON" : "OFF"), 10, 40, 20, GRAY);
            DrawText(TextFormat("- [KEY_SPACE] Random color: 0x%08x", ColorToInt(color)), 10, 70, 20, GRAY);
            DrawText(TextFormat("- [KEY_R] Random mode: %s", randomMode? "ON" : "OFF"), 10, 100, 20, GRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}