#include "player_data.h"
#include "board.h"
#include "Command.h"
#include "Registration_system.h"

class GameSession {
private:
    static const int NUMBER_OF_PLAYERS = 2;
    PlayerData gamer[NUMBER_OF_PLAYERS];
    Board board[NUMBER_OF_PLAYERS];
    int currentMove = 0;
    bool gamerReady[NUMBER_OF_PLAYERS];
    Registration_system* system;
public:
    GameSession(Registration_system& system1) : system(&system1) {};

    bool allGamersAreReady() {
        for (auto x: gamerReady) {
            if (!x) {
                return false;
            }
        }
        return true;
    }

    void login(int gamerNumber, const std::string& name, const std::string& password) {
        if (allGamersAreReady()) {
            Error_command("Error the game is already running\n").execute();
            return;
        }
        if (system->login(name, password)) {
            gamer[gamerNumber] = system->get_player_data(name, password);
        }
    }

};
