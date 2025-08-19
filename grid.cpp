#include "grid.h"
#include <iostream>

Grid::Grid() {
    rows = 20;
    columns = 10;
    cellSize = 30;
    colors = BuildColors();
    Initialize();
}

void Grid::Initialize() {
    for (int r = 0; r < rows; ++r)
        for (int c = 0; c < columns; ++c)
            grid[r][c] = 0;
}

void Grid::Draw(int offsetX, int offsetY) const {
    // background cells
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            Color col = colors[ grid[r][c] ];
            DrawRectangle(offsetX + c * cellSize + 1,
                          offsetY + r * cellSize + 1,
                          cellSize - 2, cellSize - 2, col);
        }
    }
    // border
    DrawRectangleLines(offsetX, offsetY, columns * cellSize, rows * cellSize, WHITE);
}

void Grid::Print() const {
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c)
            std::cout << grid[r][c] << ' ';
        std::cout << '\n';
    }
}

bool Grid::IsCellOutside(int row, int column) const {
    return row < 0 || row >= rows || column < 0 || column >= columns;
}

bool Grid::IsCellEmpty(int row, int column) const {
    if (IsCellOutside(row, column)) return false;
    return grid[row][column] == 0;
}

int Grid::ClearFullRows() {
    int cleared = 0;
    for (int r = rows - 1; r >= 0; --r) {
        if (IsRowFull(r)) {
            ClearRow(r);
            ++cleared;
        } else if (cleared > 0) {
            MoveRowDown(r, cleared);
        }
    }
    return cleared;
}

bool Grid::IsRowFull(int row) const {
    for (int c = 0; c < columns; ++c)
        if (grid[row][c] == 0) return false;
    return true;
}

void Grid::ClearRow(int row) {
    for (int c = 0; c < columns; ++c)
        grid[row][c] = 0;
}

void Grid::MoveRowDown(int row, int numRows) {
    for (int c = 0; c < columns; ++c) {
        grid[row + numRows][c] = grid[row][c];
        grid[row][c] = 0;
    }
}

std::vector<Color> Grid::BuildColors() const {
    // index 0 is background
    Color darkGrey = {26, 31, 40, 255}; // empty cell
    Color green    = {47, 230, 23, 255};  // S
    Color red      = {232, 18, 18, 255};  // Z
    Color orange   = {226, 116, 17, 255}; // L
    Color yellow   = {237, 234, 4, 255};  // O
    Color purple   = {166, 0, 247, 255};  // T
    Color cyan     = {21, 204, 209, 255}; // I
    Color blue     = {13, 64, 216, 255};  // J
    return { darkGrey, orange, blue, cyan, yellow, green, purple, red };
}
