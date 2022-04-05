#include "board.h"
#include <algorithm>

bool Board::isCeilFree(Coordinates c) {
    for (size_t i = std::max(0, c.x - 1); i < std::min(c.x + 1, static_cast<int>(N)); ++i) {
        for (size_t j = std::max(0, c.y - 1); j < std::min(c.y + 1, static_cast<int>(M)); ++j) {
            if (board[c.x][c.y].getShipped()) {
                return false;
            }
        }
    }
    return true;
}

Board::Board() {
    for (auto x: {4, 3, 3, 2, 2, 2, 1, 1, 1, 1}) {
        ships.emplace_back(static_cast<Ship*> (new LinearShip(x)));
    }
};

Ceil& Board::getCeil(Coordinates c) {
    return board[c.x][c.y];
}

int Board::getHealth() {
    int result = 0;
    for (auto& current_ship: ships) {
        result += current_ship->getHealth();
    }
    return result;
}

bool Board::isAllShipsSetted() {
    for (auto ship : ships) {
        if (!ship->getSetted()) {
            return false;
        }
    }
    return true;
}
