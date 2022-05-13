#include "board.h"
#include "Command.h"

bool Board::isSquareFree(Coordinates c) {
    for (size_t i = std::max(0, c.x - 1); i < std::min(c.x + 1, static_cast<int>(N)); ++i) {
        for (size_t j = std::max(0, c.y - 1); j < std::min(c.y + 1, static_cast<int>(M)); ++j) {
            if (board[i][j].getShipped()) {
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
    for (int i = 0; i < Board::N; ++i) {
        for (int j = 0; j < Board::M; ++j) {
            board[i][j].setCoordinates({i, j});
        }
    }
}

Square& Board::getSquare(Coordinates c) {
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
    for (auto ship: ships) {
        if (!ship->getSetted()) {
            return false;
        }
    }
    return true;
}

std::vector<std::pair<int, int>> Board::getUnsettedShipsList() {
    std::vector<std::pair<int, int>> result;
    for (int i = 0; i < ships.size(); ++i) {
        if (!ships[i]->getSetted()) {
            result.emplace_back(i, ships[i]->getSize());
        }
    }
    return result;
}

void Board::setShip(int shipIndex, Coordinates begin, Coordinates end) {
    auto currentShip = ships[shipIndex];
    currentShip->removeFromSea();
    if (!currentShip->canSet(begin, end, this)) {
        ErrorCommand("Can't set this ship\n").execute();
        return;
    }
    currentShip->set(begin, end, this);
}

void Board::removeShip(int shipIndex) {
    ships[shipIndex]->removeFromSea();
}

void Board::removeShip(Coordinates c) {
    if (getSquare(c).getShipped()) {
        getSquare(c).getShip()->removeFromSea();
    }
}

Mark Board::getOwnMark(Coordinates c) {
    if (getSquare(c).getShipped()) {
        return {getSquare(c).getBombed() ? 'x' : '@'};
    }
    return {'*'};
}

Mark Board::getOtherMark(Coordinates c) {
    return getSquare(c).getState();
}
