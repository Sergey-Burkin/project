#include<iostream>
class Player{
private:
    std::string name;
    std::string password;
public:
    Player();
    Player(std::string name);
    std::string getName();
    void setPassword(std::string oldPassword, std::string newPassword);
    bool verifyPassword(std::string string);
};
