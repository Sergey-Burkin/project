#include "Command.h"

#include <utility>

ErrorCommand::ErrorCommand() : message("Something went wrong!") {

}

ErrorCommand::ErrorCommand(std::string message) : message(std::move(message)) {

}

SayCommand::SayCommand() = default;

SayCommand::SayCommand(std::string message) : message(std::move(message)) {

}

LogInCommand::LogInCommand(GameSession* gameSession, int gamerIndex, std::string name,
                           std::string password) : gameSession(gameSession), gamerIndex(gamerIndex),
                                                   name(std::move(name)),
                                                   password(std::move(password)) {
}

void LogInCommand::execute() {
    gameSession->login(gamerIndex, name, password);
}
