#pragma once
#include "raylib.h"
#include <vector>

// Shared colors for grid/blocks
extern const Color DARK_GRID;
extern const Color RED_C;
extern const Color ORANGE_C;
extern const Color YELLOW_C;
extern const Color GREEN_C;
extern const Color BLUE_C;
extern const Color PURPLE_C;
extern const Color CYAN_C;
extern const Color WHITE_C;

// A vector where index 0 is empty (grid background), 1..=7 map to piece ids
std::vector<Color> GetTetrominoPalette();

