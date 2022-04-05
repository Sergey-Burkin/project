#include<ceil.h>

void Ceil::setShip(Ship& other) { ship = &other; }

void Ceil::removeShip() { ship = nullptr; }

void Ceil::bomb() { bombed = true; }

bool Ceil::getShipped() { return ship != nullptr; }

bool Ceil::getBombed() { return bombed; }

void Ceil::setState(Mark m) { state = m; }

Mark Ceil::getState() { return state; }

void Ceil::updateState() {}
