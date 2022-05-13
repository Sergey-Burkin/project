#include<square.h>

void Square::setShip(Ship& other) { ship = &other; }

void Square::removeShip() {  //see
    ship = nullptr;
}

void Square::bomb() { bombed = true; }

bool Square::getShipped() { return ship != nullptr; }

bool Square::getBombed() const { return bombed; }

void Square::setState(Mark m) { state = m; }

Mark Square::getState() { return state; }


Ship* Square::getShip() {
    return ship;
}

void Square::setCoordinates(Coordinates c) {
    coordinates = c;
}

Coordinates Square::getCoordinates() const {
    return coordinates;
}
