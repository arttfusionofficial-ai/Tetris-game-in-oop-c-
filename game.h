#pragma once
#include <vector>
#include "raylib.h"
#include "grid.h"
#include "block.h"

class Game {
public:
    Game();
    ~Game();

    void handleInput();
    void BlockMoveDown();
    void Draw();

    // Reset per your request
    void Reset();

private:
    bool BlockIsOutside(const BlockInstance& b) const;
    bool BlockFits(const BlockInstance& b) const;
    void LockBlock();

    void LoadSounds();
    void UnloadSounds();

    Grid grid;
    std::vector<BlockShape> allShapes;
    BlockInstance current;
    BlockInstance next;

    bool gameOver = false;
    int score = 0;
    int linesCleared = 0;

    // layout
    int gridOffsetX = 40;
    int gridOffsetY = 40;

    // sounds
    Sound s_lock{};
    Sound s_clear{};
    Sound s_gameover{};
    bool lockLoaded = false;
    bool clearLoaded = false;
    bool gameoverLoaded = false;
};


