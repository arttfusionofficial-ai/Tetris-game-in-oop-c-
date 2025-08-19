#pragma once

struct Position {
    int row;
    int column;
    Position() : row(0), column(0) {}
    Position(int r, int c) : row(r), column(c) {}
};
