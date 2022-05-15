#pragma once

#include "square.h"
#include "coordinates.h"
#include "ship.h"
#include "vector"

class Board {
private:
    static const size_t N = 10;
    static const size_t M = 10;
    Square board[N][M];
    std::vector<Ship*> ships;

public:
    Board();

    bool isSquareFree(Coordinates c);

    Square& getSquare(Coordinates c);

    int getHealth();

    bool isAllShipsSetted();

    std::vector<std::pair<int, int>> getUnsettedShipsList();

    void setShip(int shipIndex, Coordinates begin, Coordinates end);

    void removeShip(int shipIndex);

    void removeShip(Coordinates c);

    Mark getOwnMark(Coordinates c);

    Mark getOtherMark(Coordinates c);

    static int getN() { return N; };

    static int getM() { return M; };
};
