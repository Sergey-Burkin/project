#pragma once

#include "iostream"

#include "GameSession.h"
class GameSession;
class Board;

class Ship;
class Command {
public:
    virtual void execute() = 0;
};

class Error_command : Command {
private:
    std::string message;
public:
    Error_command();

    Error_command(const std::string& message);

    void execute() {
        std::cerr << message;
    }
};

class SayCommand : Command {
private:
    std::string message;
public:

    SayCommand();

    SayCommand(const std::string& message);

    void execute() override {
        std::cout << message;
    }
};

class LogInCommand : Command {
private:
    GameSession* gameSession;
    int gamerIndex;
    std::string name;
    std::string password;
public:
    LogInCommand(GameSession* gameSession, int gamerIndex, const std::string& name, const std::string& password);

    void execute();
};