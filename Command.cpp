//
// Created by serge on 04.04.2022.
//

#include "Command.h"

Error_command::Error_command() : message("Something went wrong!") {

}

Error_command::Error_command(const std::string& message) : message(message) {

}
