#include "ConsoleInterface.h"

int main() {
    Registration_system system;
    ConsoleInterface console;
    console.system = &system;
    console.startConsoleGame();
    return 0;
}
