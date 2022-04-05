#include "Command.h"

Error_command::Error_command() : message("Something went wrong!") {

}

Error_command::Error_command(const std::string& message) : message(message) {

}

SayCommand::SayCommand() {

}

SayCommand::SayCommand(const std::string& message) : message(message) {

}
