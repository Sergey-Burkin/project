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

    explicit Error_command(std::string message);

    void execute() override {
        std::cerr << message;
    }
};

class SayCommand : Command {
private:
    std::string message;
public:

    SayCommand();

    explicit SayCommand(std::string message);

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
    LogInCommand(GameSession* gameSession, int gamerIndex, std::string name, std::string password);

    void execute() override;
};