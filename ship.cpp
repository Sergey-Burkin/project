#include "ship.h"
#include "cmath"

void Ship::removeFromSea() {
    for (auto& current: deck) {
        current->removeShip();
        current = nullptr;
    }
    isSetted = false;
}

int Ship::getHealth() {
    int result = size;
    if (!isSetted) {
        return result;
    }
    for (auto currentDeck : deck) {
        if (currentDeck->getBombed()) {
            --result;
        }
    }
    return result;
}

LinearShip::LinearShip(size_t n) {
    size = n;
    isSetted = false;
    for (size_t i = 0; i < n; ++i) {
        deck.push_back(nullptr);
    }
}

Coordinates getIthCoordinate(Coordinates begin, Coordinates end, size_t n, size_t i) {
    return Coordinates(begin.x + (end.x - begin.x) / n * i, begin.y + (end.y - begin.y) / n * i);

}

bool LinearShip::canSet(Coordinates begin, Coordinates end, Board* board) {
    if ((begin.x == end.x) == (begin.y == end.y)) {
        return false;
    }
    if (abs(begin.x - end.x) + abs(begin.y - end.y) != size) {
        return false;
    }
    for (size_t i = 0; i < size; ++i) {
        if (!(board->isCeilFree(getIthCoordinate(begin, end, size, i)))) {
            return false;
        }
    }
    return true;
}

void LinearShip::set(Coordinates begin, Coordinates end, Board* board) {
    for (size_t i = 0; i < size; ++i) {
        Coordinates current_coordinate = getIthCoordinate(begin, end, size, i);
        deck[i] = &board->getCeil(current_coordinate);
        board->getCeil(current_coordinate).setShip(*this);
    }
}

void LinearShip::removeFromSea() {
    Ship::removeFromSea();
}

int LinearShip::getHealth() {
    return Ship::getHealth();
}
