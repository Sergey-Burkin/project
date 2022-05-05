#include<player.h>

Player::Player(std::string name, std::string password) : name(std::move(name)), password(std::move(password)) {}

std::string Player::getName() { return name; }

void Player::setPassword(const std::string& oldPassword, std::string newPassword) {
    if (oldPassword == password) {
        password = std::move(newPassword);
    }
}

bool Player::verifyPassword(const std::string& string) {
    return password == string;
}

PlayerData& Player::getData() {
    return data;
}

Player::Player() = default;