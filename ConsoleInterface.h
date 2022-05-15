#pragma once

#include <iostream>
#include "CommonInterface.h"

class ConsoleInterface : public CommonInterface {
private:
    void showField(GameSession& game, int gamerIndex, int boardIndex) override;

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
    void loginAgain(const std::string& nick, std::string& password) override;
public:
    void showLeaderBoard() override;
};