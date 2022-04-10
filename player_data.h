#pragma once

#include "string"

class PlayerData {
private:
    std::string nick_name;
    int score = 0;
public:
    void setNickName(const std::string& new_nick);

    std::string getNickName();

    int getScore();

    void addScore(int value);
};
