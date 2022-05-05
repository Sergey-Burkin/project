#pragma once

#include "GameSession.h"
#include "RegistrationSystem.h"
#include "string"
#include "vector"
#include "coordinates.h"

class CommonInterface {
protected:
    virtual void askForLogin(int userIndex, std::string& name, std::string& password) = 0;

    virtual bool askIfReady() = 0;

    virtual int askForShip(std::vector<std::pair<int, int>>& list) = 0;

    virtual Coordinates askForSquare() = 0;

    virtual void showMenu() = 0;

    virtual int getOption() = 0;

    virtual void askRegister(std::string& name, std::string& password) = 0;

    virtual void showAllBoards(GameSession& game, int playerIndex) = 0;

    virtual void loginAgain(const std::string& nick, std::string& password) = 0;

    virtual void showField(GameSession& game, int gamerIndex, int boardIndex) = 0;

    void prepareUser(GameSession& game, int userIndex);

public:
    virtual void showLeaderBoard() = 0;

    RegistrationSystem* system;

    void startGame();

    void registerPlayer();

    void newGame();
};
