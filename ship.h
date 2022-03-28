#pragma once
#include "ceil.h"
#include "coordinates.h"
#include "vector"
#include <cstddef>
class Board;
class Ship;
class Ship{
protected:
    size_t health;
    size_t size;
    bool isSetted;
    std::vector<Ceil*> deck;
};

class ShipSetter{
    virtual void setShip(Ship* ship, Coordinates begin, Coordinates end, Board* board);   
    virtual bool canSetShip(Ship* ship);
};
