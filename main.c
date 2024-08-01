#include "raylib.h"

int main(void) {
    // init
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib example program");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // update variables

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("My First Window", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // deinit
    CloseWindow();

    return 0;
}
