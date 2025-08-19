#include "game.h"
#include <cstdlib>
#include <ctime>

Game::Game() {
    InitAudioDevice();
    LoadSounds();

    allShapes = GetAllBlockShapes();
    std::srand((unsigned)std::time(nullptr));

    current = BlockInstance(allShapes[std::rand() % allShapes.size()]);
    next    = BlockInstance(allShapes[std::rand() % allShapes.size()]);
}

Game::~Game() {
    UnloadSounds();
    CloseAudioDevice();
}

void Game::Reset() {
    grid.Initialize();
    allShapes = GetAllBlockShapes();
    current = BlockInstance(allShapes[std::rand() % allShapes.size()]);
    next    = BlockInstance(allShapes[std::rand() % allShapes.size()]);
    score = 0;
    linesCleared = 0;
    gameOver = false;
}

void Game::handleInput() {
    if (gameOver) {
        if (IsKeyPressed(KEY_R)) Reset();
        return;
    }

    if (IsKeyPressed(KEY_LEFT)) {
        current.Move(0, -1);
        if (BlockIsOutside(current) || !BlockFits(current)) current.Move(0, 1);
    }
    if (IsKeyPressed(KEY_RIGHT)) {
        current.Move(0, 1);
        if (BlockIsOutside(current) || !BlockFits(current)) current.Move(0, -1);
    }
    if (IsKeyPressed(KEY_DOWN)) {
        current.Move(1, 0);
        if (BlockIsOutside(current) || !BlockFits(current)) current.Move(-1, 0);
    }
    if (IsKeyPressed(KEY_UP)) {
        current.Rotate();
        if (BlockIsOutside(current) || !BlockFits(current)) current.UndoRotate();
    }
    if (IsKeyPressed(KEY_SPACE)) {
        // Hard drop
        while (!BlockIsOutside(current) && BlockFits(current)) {
            current.Move(1, 0);
        }
        current.Move(-1, 0);
        LockBlock();
    }
    if (IsKeyPressed(KEY_R)) {
        Reset();
    }
}

void Game::BlockMoveDown() {
    if (gameOver) return;

    current.Move(1, 0);
    if (BlockIsOutside(current) || !BlockFits(current)) {
        current.Move(-1, 0);
        LockBlock(); // ensures the block is written to grid BEFORE the next spawns
    }
}

bool Game::BlockIsOutside(const BlockInstance& b) const {
    for (auto p : b.GetCellPositions())
        if (grid.IsCellOutside(p.row, p.column)) return true;
    return false;
}

bool Game::BlockFits(const BlockInstance& b) const {
    for (auto p : b.GetCellPositions())
        if (!grid.IsCellEmpty(p.row, p.column)) return false;
    return true;
}

void Game::LockBlock() {
    // write tiles
    for (auto p : current.GetCellPositions()) {
        if (!grid.IsCellOutside(p.row, p.column))
            grid.grid[p.row][p.column] = current.id;
    }
    if (lockLoaded) PlaySound(s_lock);

    // clear rows + scoring
    int cleared = grid.ClearFullRows();
    if (cleared > 0) {
        linesCleared += cleared;
        score += (cleared == 1 ? 100 : cleared == 2 ? 300 : cleared == 3 ? 500 : 800);
        if (clearLoaded) PlaySound(s_clear);
    }

    // spawn next
    current = next;
    next    = BlockInstance(allShapes[std::rand() % allShapes.size()]);
    if (!BlockFits(current)) {
        gameOver = true;
        if (gameoverLoaded) PlaySound(s_gameover);
    }
}

void Game::Draw() {
    const int cs = grid.GetCellSize();
    const auto& palette = grid.GetColors();

    // playfield background
    ClearBackground(BLACK);
    grid.Draw(gridOffsetX, gridOffsetY);

    // falling piece
    current.Draw(gridOffsetX, gridOffsetY, cs, palette);

    // UI panel (right side)
    int uiX = gridOffsetX + grid.GetColumns()*cs + 24;
    int uiY = gridOffsetY;

    DrawText("TETRIS", uiX, uiY, 26, WHITE);
    DrawText("Score:", uiX, uiY + 40, 18, WHITE);
    DrawText(TextFormat("%d", score), uiX, uiY + 62, 20, YELLOW);

    DrawText("Lines:", uiX, uiY + 96, 18, WHITE);
    DrawText(TextFormat("%d", linesCleared), uiX, uiY + 118, 20, YELLOW);

    DrawText("Next:", uiX, uiY + 152, 18, WHITE);
    // Next preview box
    int pvCell = 18;
    int pvX = uiX;
    int pvY = uiY + 178;
    DrawRectangleLines(pvX - 2, pvY - 2, pvCell * 6 + 4, pvCell * 6 + 4, WHITE);

    // draw next piece centered-ish in preview
    // normalize by removing its offsets
    for (auto p : next.GetCellPositions()) {
        int rr = p.row - next.rowOffset + 2;
        int cc = p.column - next.colOffset + 1;
        int x = pvX + cc * pvCell;
        int y = pvY + rr * pvCell;
        Color col = palette[next.id];
        DrawRectangle(x + 2, y + 2, pvCell - 4, pvCell - 4, col);
    }

    // Controls
    DrawText("Controls:", uiX, uiY + 300, 16, WHITE);
    DrawText("←/→  Move", uiX, uiY + 320, 14, WHITE);
    DrawText("↑     Rotate", uiX, uiY + 338, 14, WHITE);
    DrawText("↓     Soft drop", uiX, uiY + 356, 14, WHITE);
    DrawText("SPACE Hard drop", uiX, uiY + 374, 14, WHITE);
    DrawText("R     Restart", uiX, uiY + 392, 14, WHITE);

    if (gameOver) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.65f));
        DrawText("GAME OVER", GetScreenWidth()/2 - 110, GetScreenHeight()/2 - 40, 40, RED);
        DrawText(TextFormat("Score: %d", score), GetScreenWidth()/2 - 70, GetScreenHeight()/2 + 5, 20, WHITE);
        DrawText("Press R to restart", GetScreenWidth()/2 - 90, GetScreenHeight()/2 + 30, 18, WHITE);
    }
}

void Game::LoadSounds() {
    // If you don’t have files, either provide them or comment out these lines.
    if (FileExists("lock.wav"))     { s_lock = LoadSound("lock.wav");     lockLoaded = true; }
    if (FileExists("clear.wav"))    { s_clear = LoadSound("clear.wav");   clearLoaded = true; }
    if (FileExists("gameover.wav")) { s_gameover = LoadSound("gameover.wav"); gameoverLoaded = true; }
}

void Game::UnloadSounds() {
    if (lockLoaded)    UnloadSound(s_lock);
    if (clearLoaded)   UnloadSound(s_clear);
    if (gameoverLoaded)UnloadSound(s_gameover);
}


