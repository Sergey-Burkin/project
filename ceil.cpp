#include<ceil.h>

void Ceil::setShip(Ship& other) { ship = &other; }

void Ceil::removeShip() {  //see
    ship = nullptr;
}

void Ceil::bomb() { bombed = true; }

bool Ceil::getShipped() { return ship != nullptr; }

bool Ceil::getBombed() const { return bombed; }

void Ceil::setState(Mark m) { state = m; }

Mark Ceil::getState() { return state; }


Ship* Ceil::getShip() {
    return ship;
}
