#pragma once

#include "mark.h"

class Ship;

class Square {
private:
    Ship* ship = nullptr;
    bool bombed = false;
    Mark state = Mark('*');
public:
    void setShip(Ship& other);

    void removeShip();

    void bomb();

    bool getShipped();

    bool getBombed() const;

    void setState(Mark m);

    Mark getState();

    Ship* getShip();

};
