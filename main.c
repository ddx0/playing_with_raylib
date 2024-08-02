#include "raylib.h"
#include "./logger/logger.h"

#define LOG_FILE "./log.txt"

int main(void) {
    // setup logger
    Logger *logger = NULL;

    if ((logger = logger_create(LOG_FILE)) == NULL) {
        return -1;
    }

    // printf("POST_DESTROY: %p\n", (void *) logger);

    // setup window
    const int screenWidth = 800;
    const int screenHeight = 600;

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
    logger_destroy(&logger);

    return 0;
}
