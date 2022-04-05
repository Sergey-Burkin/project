#pragma once

#include "mark.h"

class Ship;

class Ceil {
private:
    Ship* ship = nullptr;
    bool bombed = false;
    Mark state;
public:
    void setShip(Ship& other);

    void removeShip();

    void bomb();

    bool getShipped();

    bool getBombed();

    void setState(Mark m);

    Mark getState();

    void updateState();
};
