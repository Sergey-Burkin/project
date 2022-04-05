#include "ConsoleInterface.h"

void ConsoleInterface::startConsoleGame() {
    int input = -1;
    while (input != 0) {
        std::cout <<
                  "1. Регистрация\n" <<
                  "2. Начать игру\n" <<
                  "3. Таблица рекордов\n" <<
                  "0. Выход\n";
        std::cin >> input;
        if (input == 1) {
            registerPlayer();
        } else if (input == 2) {
            newGame();
        } else if (input == 3) {
            printLeaderBoard();
        }
    }
}

void ConsoleInterface::registerPlayer() {
    std::cout << "Введи имя:\n";
    std::string name, password;
    std::cin >> name;
    std::cout << "Введи пароль:\n";
    std::cin >> password;
    system->register_new_player(name, password);
}

void ConsoleInterface::newGame() {
    GameSession gameSession(*system);

}

void ConsoleInterface::printLeaderBoard() {
    auto vector = system->getLeaderScore();
    for (auto pair : vector) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
}
