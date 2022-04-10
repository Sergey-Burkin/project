#include<coordinates.h>

Coordinates::Coordinates() = default;

Coordinates::Coordinates(int x, int y) : x(x), y(y) {}

Coordinates::Coordinates(std::string s) : x(s[0] - 'A'), y(s[1] - '0') {}

