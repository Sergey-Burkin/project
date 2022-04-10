#pragma once

#include "player_data.h"
#include "board.h"
#include "Command.h"
#include "Registration_system.h"

class Registration_system;

class GameSession {
private:
    static const int NUMBER_OF_PLAYERS = 2;
    std::string gamerName[NUMBER_OF_PLAYERS];
    PlayerData gamer[NUMBER_OF_PLAYERS];
    Board board[NUMBER_OF_PLAYERS];
    int currentMove = 0;
    bool gamerReady[NUMBER_OF_PLAYERS];
    bool gamerLogged[NUMBER_OF_PLAYERS];
    Registration_system* system;
    int theWinner = -1;

    void assertIndex(int gamerIndex);

    void assertGameEnd();

public:
    GameSession(Registration_system& system1) : system(&system1) {};

    bool allGamersAreReady();

    void login(int gamerIndex, const std::string& name, const std::string& password);

    void nextMove();

    void setShip(int gamerIndex, int shipIndex, Coordinates begin, Coordinates end);

    void removeShip(int gamerIndex, int shipIndex);

    void removeShip(int gamerIndex, Coordinates c);

    void ready(int gamerIndex);

    void bomb(int gamerIndex, int otherGamerIndex, Coordinates c);

    Mark getMark(int gamerIndex, int boardIndex, Coordinates c);

    int getBoardHeight(int boardIndex);

    int getBoardWidth(int boardIndex);

    bool getLogged(int gamerIndex);

    int getNumberOfPlayers();

    std::vector<std::pair<int, int>> getFreeShips(int gamerIndex);

    int getCurrentPlayer();

    PlayerData getPlayerData(int playerIndex);

    int getWinner();

    std::string getGamerName(int gamerIndex);
};
