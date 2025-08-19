 #include "colors.h"

const Color DARK_GRID  = {26, 31, 40, 255};
const Color RED_C      = {232,  18,  18, 255};
const Color ORANGE_C   = {226, 116,  17, 255};
const Color YELLOW_C   = {237, 234,   4, 255};
const Color GREEN_C    = { 47, 230,  23, 255};
const Color BLUE_C     = { 13,  64, 216, 255};
const Color PURPLE_C   = {166,   0, 247, 255};
const Color CYAN_C     = { 21, 204, 209, 255};
const Color WHITE_C    = {255, 255, 255, 255};

std::vector<Color> GetTetrominoPalette() {
    // index 0 is used as grid background color (empty)
    return { DARK_GRID, ORANGE_C, BLUE_C, CYAN_C, YELLOW_C, GREEN_C, PURPLE_C, RED_C };
}