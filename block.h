#pragma once
#include <vector>
#include "raylib.h"
#include "position.h"

// Shape (definition) of a tetromino
struct BlockShape {
    int id = 0;                                        // 1..7
    std::vector<std::vector<Position>> cells;          // rotation states (each 4 tiles)
    int spawnRowOffset = 0;                            // starting row offset
    int spawnColOffset = 0;                            // starting col offset
};

// All 7 shapes
std::vector<BlockShape> GetAllBlockShapes();

// A live, falling tetromino
class BlockInstance {
public:
    BlockInstance() = default;
    explicit BlockInstance(const BlockShape& s);

    void Draw(int offsetX, int offsetY, int cellSize, const std::vector<Color>& palette) const;
    void Move(int dRow, int dCol);
    void Rotate();
    void UndoRotate();

    std::vector<Position> GetCellPositions() const;

    // Public state used by UI preview
    int id = 0;
    int rowOffset = 0;
    int colOffset = 0;
    int rotationState = 0;

private:
    BlockShape shape;
};

