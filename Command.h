#pragma once
#include "iostream"
class Command {
public:
    virtual void execute() = 0;
};

class Error_command : Command{
private:
    std::string message;
public:
    Error_command();
    Error_command(const std::string& message);
    void execute() {
        std::cerr << message;
    }
};