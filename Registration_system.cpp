#include "Registration_system.h"

bool Registration_system::is_player_exists(const std::string& name) {
    for (auto& person: data) {
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
    data.back().get_data().setNickName(name);
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

bool Registration_system::login(const std::string& name, const std::string& password) {
    if (!is_player_exists(name)) {
        Error_command errorCommand("Can't find user " + name + '\n');
        errorCommand.execute();
        return false;
    }
    for (auto& player: data) {
        if (player.getName() == name) {
            if (player.verifyPassword(password)) {
                return true;
            }
            Error_command errorCommand("The password is wrong!\n");
            errorCommand.execute();
            return false;
        }
    }
    return false;
}

PlayerData& Registration_system::get_player_data(const std::string& name, const std::string& password) {
    if (!login(name, password)) {
        throw "Error";
    }
    for (auto& player: data) {
        if (player.getName() == name) {
            return player.get_data();
        }
    }
    throw "Error";
}

void Registration_system::addPlayerScore(const std::string& name, int score) {
    if (!is_player_exists(name)) {
        Error_command("Error no such user!\n").execute();
        return;
    }
    for (auto& player: data) {
        if (player.getName() == name) {
            player.get_data().addScore(score);
        }
    }
}

std::vector<std::pair<std::string, int>> Registration_system::getLeaderScore() {
    std::vector<std::pair<std::string, int>> result;
    for (auto player: data) {
        result.emplace_back(std::make_pair(player.get_data().getNickName(), player.get_data().getScore()));
    }
    return result;
}
