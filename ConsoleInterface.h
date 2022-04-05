#pragma once
#include <iostream>
#include "GameSession.h"
#include "Registration_system.h"
class ConsoleInterface {
public:
    void startConsoleGame();
    Registration_system* system;
    void registerPlayer();
    void newGame();
    void printLeaderBoard();
};