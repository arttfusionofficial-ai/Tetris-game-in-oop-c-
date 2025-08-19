#pragma once
#include <vector>
#include "raylib.h"

class Grid {
public:
    Grid();

    void Initialize();
    void Draw(int offsetX, int offsetY) const;
    void Print() const;

    bool IsCellOutside(int row, int column) const;
    bool IsCellEmpty(int row, int column) const;

    int ClearFullRows();                   // returns # of cleared lines

    // Accessors
    int GetRows() const { return rows; }
    int GetColumns() const { return columns; }
    int GetCellSize() const { return cellSize; }
    const std::vector<Color>& GetColors() const { return colors; }

    int grid[20][10]; // 20 rows x 10 columns, values 0..7 (0=empty)

private:
    std::vector<Color> BuildColors() const;
    bool IsRowFull(int row) const;
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);

    int rows;
    int columns;
    int cellSize;
    std::vector<Color> colors;
};

