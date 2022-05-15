#pragma once

#include <iostream>
#include "GameSession.h"
#include "Registration_system.h"

class ConsoleInterface {
private:
    static void printField(GameSession& game, int gamerIndex, int boardIndex);

    void prepareUser(GameSession& game, int userIndex);

    template<typename T>
    void read(T& object);

public:
    void startConsoleGame();

    Registration_system* system;

    void registerPlayer();

    void newGame();

    void printLeaderBoard() const;
};