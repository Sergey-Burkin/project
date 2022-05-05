#pragma  once

#include "player.h"
#include "vector"
#include "Command.h"
#include "algorithm"

class RegistrationSystem {
private:
    std::vector<Player> data;
public:
    bool isPlayerExists(const std::string& name);

    void registerNewPlayer(const std::string& name, const std::string& password);

    void removePlayer(const std::string& name);

    bool login(const std::string& name, const std::string& password);

    PlayerData& getPlayerData(const std::string& name, const std::string& password);

    void addPlayerScore(const std::string& name, int score);

    std::vector<std::pair<std::string, int>> getLeaderScore();

    int getNumberOfUsers();
};