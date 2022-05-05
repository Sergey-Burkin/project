#pragma once

#include <iostream>
#include "GameSession.h"
#include "Registration_system.h"
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
    virtual void relogin(const std::string& nick, std::string& password) = 0;

public:
    virtual void showLeaderBoard() = 0;

};
