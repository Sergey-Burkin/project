#include<iostream>
#include<player.h>

int main() {
    std::string s = "Name";
    Player gamma(s);
    std::cout << gamma.getName(); 
    return 0;
}
