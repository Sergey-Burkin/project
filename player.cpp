#include<player.h>

Player::Player(std::string name) : name (name) {};
std::string Player::getName() {return name;}
void Player::setPassword(std::string oldPassword, std::string newPassword) {
   if (oldPassword == password){
       password = newPassword;
   }
}
bool Player::verifyPassword(std::string string) {
    return password == string;
}
