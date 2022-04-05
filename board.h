#pragma once

#include "ceil.h"
#include "coordinates.h"
#include "ship.h"
#include "vector"

class Board {
private:
    static const size_t N = 10;
    static const size_t M = 10;
    Ceil board[N][M];
    std::vector<Ship*> ships;

public:
    Board();

    bool isCeilFree(Coordinates c);

    Ceil& getCeil(Coordinates c);

    int getHealth();

    bool isAllShipsSetted();

    std::vector<int> getUnsettedShipsList();

    void setShip(int shipIndex, Coordinates begin, Coordinates end);

    void removeShip(int shipIndex);

    void removeShip(Coordinates c);

    Mark getOwnMark(Coordinates c);
    Mark getOtherMark(Coordinates c);

    int getN() {return N;};
    int getM() {return M;};
};
