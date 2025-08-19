#include "raylib.h"
#include "game.h"

static double s_lastUpdate = 0.0;
static bool EventTriggered(double intervalSec) {
    double now = GetTime();
    if (now - s_lastUpdate >= intervalSec) {
        s_lastUpdate = now;
        return true;
    }
    return false;
}

int main() {
    const int cellSize = 30;
    const int rows = 20, cols = 10;
    const int gridW = cols * cellSize;
    const int gridH = rows * cellSize;

    const int marginL = 40;
    const int marginT = 40;
    const int sidePanelW = 220;

    InitWindow(marginL + gridW + sidePanelW + marginL, marginT + gridH + marginT, "Tetris (raylib)");
    SetTargetFPS(60);

    Game game;

    // gravity parameters
    double dropInterval = 0.5; // seconds
    while (!WindowShouldClose()) {
        game.handleInput();

        // simple speed-up: every ~20 seconds a tiny bit faster
        if (EventTriggered(0.02)) {
            // noop: small tick used only to keep internal time running uniformly
        }
        if (EventTriggered(dropInterval)) {
            game.BlockMoveDown();
        }

        BeginDrawing();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}