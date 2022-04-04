#include<player.h>

Player::Player(std::string name, std::string password) : name (name), password(password) {};
std::string Player::getName() {return name;}
void Player::setPassword(std::string oldPassword, std::string newPassword) {
   if (oldPassword == password){
       password = newPassword;
   }
}
bool Player::verifyPassword(std::string string) {
    return password == string;
}

Player_data& Player::get_data() {
    return data;
}
