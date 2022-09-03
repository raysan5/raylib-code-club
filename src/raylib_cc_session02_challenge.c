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
    
    // TODO 01: Define required variables
    int currentShape = SHAPE_TRIANGLE;
    bool linesMode = false;
    Color color = RED;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO 02: Select current shape to draw
        
        // TODO 03: Toogle lines drawing mode

        // TODO 04: Random color selector

        // TODO 05: Enable random mode and process
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            // TODO 06: Draw 2d grid for convenience

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
            
            // TODO 07: Draw shapes information 

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}