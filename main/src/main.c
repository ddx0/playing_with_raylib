#include "raylib.h"
#include "../../logger/include/logger.h"

#define LOG_FILE "./log.txt"

double constrain_itod(int num1, int num2, int val);

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

// map (val) between range (num1, num2) and return between 0.0-1.0
double constrain_itod(int num1, int num2, int val) {
    // ensure num1 represents min, num2 represents max
    if (num1 > num2) {
        int temp = num1;
        num1 = num2;
        num2 = temp;
    }
    // clamp
    val = (val < num1) ? num1 : val;
    val = (val > num2) ? num2 : val;
    // constrain between 0.0-1.0
    unsigned int range_total = abs(num2 - num1);
    unsigned int range_val = abs(val - num1);
    double constrain = (double) range_val / (double) range_total;
    // printf("min: %d\nmax: %d\nval: %d\n", num1, num2, val);
    // printf("range total: %u\nrange val: %d\nconstraint: %lf\n", range_total, range_val, constrain);
    return constrain;
}
