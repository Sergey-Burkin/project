#pragma once
#include "Registration_system.h"

bool Registration_system::is_player_exists(std::string name) {
    for (auto& person : data) {
        if (person.getName() == name) {
            return true;
        }
    }
    return false;
}

void Registration_system::register_new_player(const std::string& name, const std::string& password) {
    if (is_player_exists(name)) {
        Error_command errorCommand("Error user already exists!\n");
        errorCommand.execute();
        return;
    }
    data.emplace_back(name, password);
}

void Registration_system::remove_player(const std::string& name) {
    if (!is_player_exists(name)) {
        Error_command errorCommand("Can't find user " + name + "\n");
        errorCommand.execute();
        return;
    }
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (it->getName() == name) {
            data.erase(it);
            return;
        }
    }
}

bool Registration_system::login(std::string name, std::string password) {
    if (!is_player_exists(name)) {
        Error_command errorCommand("Can't finde user" + name + '\n');
        errorCommand.execute();
        return false;
    }
    for (auto& player : data) {
        if (player.getName() == name) {
            if (player.verifyPassword(password)) {
                return true;
            }
            Error_command errorCommand("The password is wrong!\n");
            errorCommand.execute();
            return false;
        }
    }
}
