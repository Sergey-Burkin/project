#pragma once

#include "player_data.h"
#include "board.h"
#include "Command.h"
#include "RegistrationSystem.h"

class RegistrationSystem;

class GameSession {
private:
    static const int NUMBER_OF_PLAYERS = 2;
    std::string gamerName[NUMBER_OF_PLAYERS];
    PlayerData gamer[NUMBER_OF_PLAYERS];
    Board board[NUMBER_OF_PLAYERS];
    int currentMove = 0;
    bool gamerReady[NUMBER_OF_PLAYERS];
    bool gamerLogged[NUMBER_OF_PLAYERS];
    RegistrationSystem* system;
    int theWinner = -1;

    void assertIndex(int gamerIndex) const;

    void assertGameEnd() const;

    void markNeighbourSquare(int gamerIndex, Coordinates c, bool verticalAndHorizontal);

public:
    explicit GameSession(RegistrationSystem& system);;

    bool allGamersAreReady();

    void login(int gamerIndex, const std::string& name, const std::string& password);

    void nextMove();

    void setShip(int gamerIndex, int shipIndex, Coordinates begin, Coordinates end);

    void removeShip(int gamerIndex, Coordinates c);

    void ready(int gamerIndex);

    void bomb(int gamerIndex, int otherGamerIndex, Coordinates c);

    Mark getMark(int gamerIndex, int boardIndex, Coordinates c);

    int getBoardHeight(int boardIndex);

    int getBoardWidth(int boardIndex);

    bool getLogged(int gamerIndex);

    static int getNumberOfPlayers();

    std::vector<std::pair<int, int>> getFreeShips(int gamerIndex);

    int getCurrentPlayer() const;

    PlayerData getPlayerData(int playerIndex);

    int getWinner() const;

    std::string getGamerName(int gamerIndex);
};
