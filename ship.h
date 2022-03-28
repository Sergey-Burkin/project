#pragma once
#include "ceil.h"
#include "coordinates.h"
#include "vector"
#include <cstddef>
#include "board.h"
class Board;
class Ship{
protected:
    size_t health;
    size_t size;
    bool isSetted;
    std::vector<Ceil*> deck;
public:
    void removeFromSea();
    virtual bool canSet(Coordinates begin, Coordinates end, Board* board) = 0;
    virtual void set(Coordinates begin, Coordinates end, Board* board) = 0;
};

class LinearShip : Ship {
public:
    LinearShip(size_t n);    
    bool canSet(Coordinates begin, Coordinates end, Board* board);
    void set(Coordinates begin, Coordinates end, Board* board);
};
