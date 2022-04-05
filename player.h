#include<string>
#include "player_data.h"

#pragma once

class Player {
private:
    std::string name;
    std::string password;
    PlayerData data;
public:
    Player();

    Player(std::string name, std::string password);

    std::string getName();

    void setPassword(std::string oldPassword, std::string newPassword);

    bool verifyPassword(std::string string);

    PlayerData& get_data();
};
