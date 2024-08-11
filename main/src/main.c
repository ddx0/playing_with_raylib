#include "raylib.h"
#include "logger.h"
#include <stdio.h>

#define CREATE_ERR_STR(charbuf, bufsize, msg) snprintf(charbuf, bufsize, "ERROR: %s: " msg "\n", __FUNCTION__); fflush(charbuf);
// config logger
#define LOG_FILE "./log.txt"
#define PATH_SIZE 256
// config window
#define INIT_WINDOW_WIDTH 800
#define INIT_WINDOW_HEIGHT 600
#define INIT_WINDOW_NAME "playing with raylib"

// util
double constrain_itod(int x, int y, int val);

int main(void) {
    Logger *logger = logger_create();

    if (!logger) {
        fprintf(stderr, "logger could not be initialized, skipping...\n");
    } else {
        logger_set_logger(logger, LOG_FILE);
    }

    // we can't grab size data before InitWindow(), so launch first?
    // - apparently can't grab actual monitor size after InitWindow(), so hardcoded start size seemingly necessary
    InitWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, INIT_WINDOW_NAME);

    const int renderWidth = GetRenderWidth();//GetMonitorWidth(GetCurrentMonitor());
    const int screenWidth = GetScreenWidth();//GetMonitorHeight(GetCurrentMonitor());
    const int monitorWidth = GetMonitorWidth(GetMonitorCount());
    char buff[128] = {0};
    snprintf(buff, 128, "\nrenderWidth:  %6d\nscreenWidth:  %6d\nmonitorWidth: %6d\n", renderWidth, screenWidth, monitorWidth);
    logger_sendmsg(logger, buff);

    SetTargetFPS(60);

    while (0/*!WindowShouldClose()*/) {
        // update variables

        // draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        int screenwidth = GetScreenWidth();
        int renderwidth = GetRenderWidth();
        int monitorwidth = GetMonitorWidth(GetCurrentMonitor());
        char width_str[128] = {0};
        snprintf(width_str, 128, "S_WIDTH: %d --- R_WIDTH: %d --- M_WIDTH: %d", screenwidth, renderwidth, monitorwidth);
        DrawText(width_str, 100, 100, 25, RED);
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
