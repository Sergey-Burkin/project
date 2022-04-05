#pragma once

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
    int theWinner = -1;
    void assertNumber(int gameNumber);
    void assertGameEnd();

public:
    GameSession(Registration_system& system1) : system(&system1) {};

    bool allGamersAreReady();

    void login(int gamerNumber, const std::string& name, const std::string& password);

    void nextMove();

    void setShip(int gameNumber, int shipNumber, Coordinates begin, Coordinates end);

    void removeShip(int gamerIndex, int shipIndex);

    void removeShip(int gamerIndex, Coordinates c);

    void ready(int gamerIndex);

    void bomb(int gamerIndex, int otherGamerIndex, Coordinates c);

    Mark getMark(int gamerIndex, int boardIndex, Coordinates c);
};
