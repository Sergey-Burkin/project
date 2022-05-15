#pragma  once

#include "player.h"
#include "vector"
#include "Command.h"
#include "algorithm"

class Registration_system {
private:
    std::vector<Player> data;
public:
    bool is_player_exists(const std::string& name);

    void register_new_player(const std::string& name, const std::string& password);

    void remove_player(const std::string& name);

    bool login(const std::string& name, const std::string& password);

    PlayerData& get_player_data(const std::string& name, const std::string& password);

    void addPlayerScore(const std::string& name, int score);

    std::vector<std::pair<std::string, int>> getLeaderScore();
};