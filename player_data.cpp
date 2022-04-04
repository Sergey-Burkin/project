#include "player_data.h"

void Player_data::set_nick_name(const std::string& new_nick) {
    nick_name = new_nick;
}

std::string Player_data::get_nick_name() {
    return nick_name;
}

int Player_data::get_score() {
    return score;
}

void Player_data::add_score(int value) {
    score += value;
}
