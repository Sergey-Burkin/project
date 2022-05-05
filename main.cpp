#include "ConsoleInterface.h"

int main() {
    RegistrationSystem system;
    ConsoleInterface console;
    console.system = &system;
    console.startGame();
    return 0;
}
