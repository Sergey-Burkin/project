#include "Command.h"

Error_command::Error_command() : message("Something went wrong!") {

}

Error_command::Error_command(const std::string& message) : message(message) {

}

SayCommand::SayCommand() {

}

SayCommand::SayCommand(const std::string& message) : message(message) {

}

LogInCommand::LogInCommand(GameSession* gameSession, int gamerIndex, const std::string& name,
                           const std::string& password) : gameSession(gameSession), gamerIndex(gamerIndex), name(name),
                                                          password(password) {
}

void LogInCommand::execute() {
    gameSession->login(gamerIndex, name, password);
}
