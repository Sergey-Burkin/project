#include "ConsoleInterface.h"

template<typename T>
void ConsoleInterface::read(T& object) {
    std::cin >> object;
    while (!std::cin) {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        ErrorCommand("Invalid input! Try again: \n").execute();
        std::cin >> object;
    }
}

void ConsoleInterface::showField(GameSession& game, int gamerIndex, int boardIndex) {
    std::cout << "+";
    for (size_t j = 0; j < game.getBoardWidth(boardIndex); ++j) {
        std::cout << j;
    }
    std::cout << '\n';
    for (size_t i = 0; i < game.getBoardHeight(boardIndex); ++i) {
        std::cout << static_cast<char>('A' + i);
        for (size_t j = 0; j < game.getBoardWidth(boardIndex); ++j) {
            std::cout << game.getMark(gamerIndex, boardIndex, {static_cast<int>(i), static_cast<int>(j)}).mark;
        }
        std::cout << "\n";
    }
}

void ConsoleInterface::askForLogin(int userIndex, std::string& name, std::string& password) {
    std::cout << "Игрок " + std::to_string(userIndex) + ", залогинься:\n";
    read(name);
    read(password);
}

bool ConsoleInterface::askIfReady() {
    std::cout << "Готов y/n?\n";
    std::string s;
    read(s);
    return s[0] == 'y' or s[0] == 'Y';
}

int ConsoleInterface::askForShip(std::vector<std::pair<int, int>>& list) {
    int shipIndex = -2;
    int numberOfShips = list.size();
    while (!(shipIndex >= -1 && 0 < numberOfShips - shipIndex)) {
        std::cout << "Выберите корабль:\n";
        for (int i = 0; i < numberOfShips; ++i) {
            std::cout << i << ' ';
            for (int j = 0; j < list[i].second; ++j) {
                std::cout << "S";
            }
            std::cout << '\n';
        }
        std::cout << "-1 - Убрать корабль\n";
        read(shipIndex);
    }
    return shipIndex;
}

bool goodString(const std::string& s) {
    auto goodInt = [](int x) { return 0 <= x && x < 10; };
    if (s.size() != 2) { return false; }
    int x = s[0] - 'A';
    int y = s[1] - '0';
    return goodInt(x) && goodInt(y);
}

Coordinates ConsoleInterface::askForSquare() {
    std::string s;
    while (!goodString(s)) {
        std::cout << "Укажите клетку (например, A5)\n";
        read(s);
        if (!goodString(s)) {
            ErrorCommand("Format Error\n").execute();
        }
    }
    return {s};
}

void ConsoleInterface::showMenu() {
    std::cout <<
              "1. Регистрация\n" <<
              "2. Начать игру\n" <<
              "3. Таблица рекордов\n" <<
              "0. Выход\n";
}

int ConsoleInterface::getOption() {
    int x;
    read(x);
    return x;
}

void ConsoleInterface::askRegister(std::string& name, std::string& password) {

    std::cout << "Введите имя:\n";
    read(name);
    std::cout << "Введите пароль:\n";
    read(password);
}

void ConsoleInterface::showAllBoards(GameSession& game, int playerIndex) {
    for (int i = 0; i < game.getNumberOfPlayers(); ++i) {
        SayCommand("Доска игрока " + game.getPlayerData(i).getNickName() + "\n").execute();
        showField(game, playerIndex, i);
        std::cout << '\n';
    }
}

void ConsoleInterface::loginAgain(const std::string& nick, std::string& password) {
    SayCommand("Введте пароль снова, " + nick + "\n").execute();
    read(password);
}

void ConsoleInterface::showLeaderBoard() {
    auto vector = system->getLeaderScore();
    for (auto& pair: vector) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
}

