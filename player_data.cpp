#include "player_data.h"

void PlayerData::setNickName(const std::string& new_nick) {
    nick_name = new_nick;
}

std::string PlayerData::getNickName() {
    return nick_name;
}

int PlayerData::getScore() {
    return score;
}

void PlayerData::addScore(int value) {
    score += value;
}
