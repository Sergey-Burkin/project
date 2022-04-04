#include "player.h"
#include "vector"
#include "Command.h"
#include "algorithm"
class Registration_system {
private:
    std::vector<Player> data;
public:
    bool is_player_exists(std::string name);
    void register_new_player(const std::string& name, const std::string& password);
    void remove_player(const std::string& name);
    bool login(std::string name, std::string password);
};