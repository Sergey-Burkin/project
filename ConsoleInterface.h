#pragma once

#include <iostream>
#include "GameSession.h"
#include "Registration_system.h"
#include "CommonInterface.h"

class ConsoleInterface : public CommonInterface {
private:
    static void printField(GameSession& game, int gamerIndex, int boardIndex);

    void prepareUser(GameSession& game, int userIndex);

    template<typename T>
    void read(T& object);
    void askForLogin(int userIndex, std::string& name, std::string& password) override;
    bool askIfReady() override;
    int askForShip(std::vector<std::pair<int, int>>& list) override;
    Coordinates askForSquare() override;
    void showMenu() override;
    int getOption() override;
    void askRegister(std::string& name, std::string& password) override;
    void showAllBoards(GameSession& game, int playerIndex) override;
    void relogin(const std::string& nick, std::string& password) override;
public:

    void startConsoleGame();

    Registration_system* system;

    void registerPlayer();

    void newGame();

    void showLeaderBoard() override;
};