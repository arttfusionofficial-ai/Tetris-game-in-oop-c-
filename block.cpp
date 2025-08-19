#include "block.h"

BlockInstance::BlockInstance(const BlockShape& s) {
    shape = s;
    id = s.id;
    rotationState = 0;
    rowOffset = s.spawnRowOffset;
    colOffset = s.spawnColOffset;
}

void BlockInstance::Draw(int offsetX, int offsetY, int cellSize, const std::vector<Color>& palette) const {
    for (auto& p : GetCellPositions()) {
        DrawRectangle(p.column * cellSize + offsetX + 1,
                      p.row    * cellSize + offsetY + 1,
                      cellSize - 2, cellSize - 2, palette[id]);
    }
}

void BlockInstance::Move(int dRow, int dCol) {
    rowOffset += dRow;
    colOffset += dCol;
}

void BlockInstance::Rotate() {
    rotationState = (rotationState + 1) % (int)shape.cells.size();
}

void BlockInstance::UndoRotate() {
    rotationState = (rotationState - 1 + (int)shape.cells.size()) % (int)shape.cells.size();
}

std::vector<Position> BlockInstance::GetCellPositions() const {
    std::vector<Position> out;
    const auto& tiles = shape.cells[rotationState];
    out.reserve(tiles.size());
    for (const auto& t : tiles) {
        out.emplace_back(t.row + rowOffset, t.column + colOffset);
    }
    return out;
}

// ===== 7 classic tetromino shapes =====
std::vector<BlockShape> GetAllBlockShapes() {
    std::vector<BlockShape> S;

    // Palette indices (1..7) map to colors in Grid::GetColors()

    // L
    S.push_back(BlockShape{
        1,
        {
            { {0,2},{1,0},{1,1},{1,2} },
            { {0,1},{1,1},{2,1},{2,2} },
            { {1,0},{1,1},{1,2},{2,0} },
            { {0,0},{0,1},{0,2},{1,2} },
        },
        0, 3
    });

    // J
    S.push_back(BlockShape{
        2,
        {
            { {0,0},{1,0},{1,1},{1,2} },
            { {0,1},{0,2},{1,1},{2,1} },
            { {1,0},{1,1},{1,2},{2,2} },
            { {0,1},{1,1},{2,0},{2,1} },
        },
        0, 3
    });

    // I
    S.push_back(BlockShape{
        3,
        {
            { {1,0},{1,1},{1,2},{1,3} },
            { {0,2},{1,2},{2,2},{3,2} },
            { {2,0},{2,1},{2,2},{2,3} },
            { {0,1},{1,1},{2,1},{3,1} },
        },
        -1, 3
    });

    // O
    S.push_back(BlockShape{
        4,
        {
            { {0,0},{0,1},{1,0},{1,1} },
            { {0,0},{0,1},{1,0},{1,1} },
            { {0,0},{0,1},{1,0},{1,1} },
            { {0,0},{0,1},{1,0},{1,1} },
        },
        0, 4
    });

    // S
    S.push_back(BlockShape{
        5,
        {
            { {1,0},{2,0},{0,1},{1,1} },
            { {1,0},{1,1},{2,1},{2,2} },
            { {1,0},{2,0},{0,1},{1,1} },
            { {1,0},{1,1},{2,1},{2,2} },
        },
        0, 3
    });

    // T
    S.push_back(BlockShape{
        6,
        {
            { {1,0},{0,1},{1,1},{2,1} },
            { {1,0},{1,1},{1,2},{2,1} },
            { {0,1},{1,1},{2,1},{1,2} },
            { {0,1},{1,0},{1,1},{1,2} },
        },
        0, 3
    });

    // Z
    S.push_back(BlockShape{
        7,
        {
            { {0,0},{1,0},{1,1},{2,1} },
            { {1,0},{1,1},{2,1},{2,2} },
            { {0,0},{1,0},{1,1},{2,1} },
            { {1,0},{1,1},{2,1},{2,2} },
        },
        0, 3
    });

    return S;
}


