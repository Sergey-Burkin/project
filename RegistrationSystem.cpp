#include "RegistrationSystem.h"

bool RegistrationSystem::isPlayerExists(const std::string& name) {
    for (auto& person: data) {
        if (person.getName() == name) {
            return true;
        }
    }
    return false;
}

void RegistrationSystem::registerNewPlayer(const std::string& name, const std::string& password) {
    if (isPlayerExists(name)) {
        ErrorCommand errorCommand("Error user already exists!\n");
        errorCommand.execute();
        return;
    }
    data.emplace_back(name, password);
    data.back().getData().setNickName(name);
}

void RegistrationSystem::removePlayer(const std::string& name) {
    if (!isPlayerExists(name)) {
        ErrorCommand errorCommand("Can't find user " + name + "\n");
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

bool RegistrationSystem::login(const std::string& name, const std::string& password) {
    if (!isPlayerExists(name)) {
        ErrorCommand errorCommand("Can't find user " + name + '\n');
        errorCommand.execute();
        return false;
    }
    for (auto& player: data) {
        if (player.getName() == name) {
            if (player.verifyPassword(password)) {
                return true;
            }
            ErrorCommand errorCommand("The password is wrong!\n");
            errorCommand.execute();
            return false;
        }
    }
    return false;
}

PlayerData& RegistrationSystem::getPlayerData(const std::string& name, const std::string& password) {
    if (!login(name, password)) {
        throw "Error";
    }
    for (auto& player: data) {
        if (player.getName() == name) {
            return player.getData();
        }
    }
    throw "Error";
}

void RegistrationSystem::addPlayerScore(const std::string& name, int score) {
    if (!isPlayerExists(name)) {
        ErrorCommand("Error no such user!\n").execute();
        return;
    }
    for (auto& player: data) {
        if (player.getName() == name) {
            player.getData().addScore(score);
        }
    }
}

std::vector<std::pair<std::string, int>> RegistrationSystem::getLeaderScore() {
    std::vector<std::pair<std::string, int>> result;
    for (auto player: data) {
        result.emplace_back(std::make_pair(player.getData().getNickName(), player.getData().getScore()));
    }
    return result;
}

int RegistrationSystem::getNumberOfUsers() {
    return data.size();
}