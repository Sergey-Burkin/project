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

    void setPassword(const std::string& oldPassword, std::string newPassword);

    bool verifyPassword(const std::string& string);

    PlayerData& getData();
};
