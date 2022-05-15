#pragma once

#include "iostream"
#include <cstddef>

class Coordinates {
public:
    int x = 0;
    int y = 0;

    Coordinates();

    Coordinates(int x, int y);

    Coordinates(std::string s);
};
