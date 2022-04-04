#include<iostream>
#include "player.h"
#include "board.h"
#include "coordinates.h"
int main() {
    std::string s = "Name";
    Player gamma(s, std::string());
    Board b;
    Coordinates c(0, 0);
    std::cout << gamma.getName() << b.isCeilFree(c) << '\n'; 
    return 0;
}
