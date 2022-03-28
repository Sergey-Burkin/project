#pragma once
#include "ceil.h"
#include "coordinates.h"
#include "ship.h"
#include "vector"
class Board{
private:
    static const int N = 10;
    static const int M = 10;
    Ceil board[N][M];
    std::vector<Ship*> ships;

public:
    Board();
    bool isCeilFree(Coordinates c);

};
