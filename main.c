#include "raylib.h"
#include "./logger/logger.h"

#define LOG_FILE "./log.txt"

int main(void) {
    // setup logger
    Logger *logger = NULL;

    if ((logger = logger_create(LOG_FILE)) == NULL) {
        return -1;
    }

    logger_destroy(&logger);

    // printf("POST_DESTROY: %p\n", (void *) logger);

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
