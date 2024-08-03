#include "raylib.h"
#include "../../logger/include/logger.h"

#define LOG_FILE "./log.txt"

double constrain_itod(int x, int y, int val);

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
        int screenwidth = GetScreenWidth();
        int renderwidth = GetRenderWidth();
        int monitorwidth = GetMonitorWidth(GetCurrentMonitor());
        char width_str[128] = {0};
        snprintf(width_str, 128, "S_WIDTH: %d --- R_WIDTH: %d --- M_WIDTH: %d", screenwidth, renderwidth, monitorwidth);
        DrawText(width_str, 100, 100, 15, RED);
        EndDrawing();
    }
    // deinit
    CloseWindow();
    logger_destroy(&logger);

    return 0;
}

// map (val) between range (x, y) and return between 0.0-1.0
double constrain_itod(int x, int y, int val) {
    // ensure num1 represents min, num2 represents max
    if (x > y) {
        x ^= y;
        y ^= x;
        x ^= y;
    }
    // clamp
    val = (val < x) ? x : val;
    val = (val > y) ? y : val;
    // constrain between 0.0-1.0
    unsigned int range_total = abs(y - x);
    unsigned int range_val = abs(val - x);
    double constrain = (double) range_val / (double) range_total;
    // printf("min: %d\nmax: %d\nval: %d\n", num1, num2, val);
    // printf("range total: %u\nrange val: %d\nconstraint: %lf\n", range_total, range_val, constrain);
    return constrain;
}
