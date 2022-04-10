#include "ConsoleInterface.h"

void ConsoleInterface::printField(GameSession& game, int gamerIndex, int boardIndex) {
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

void ConsoleInterface::prepareUser(GameSession& game, int userIndex) {
    while (!game.getLogged(userIndex)) {
        std::cout << "Игрок " + std::to_string(userIndex) + ", залогинься:\n";
        std::string name, password;
        read(name);
        read(password);
        LogInCommand(&game, userIndex, name, password).execute();
    }
    bool ready = false;
    while (!ready) {
        printField(game, userIndex, userIndex);
        auto shipList = game.getFreeShips(userIndex);
        if (shipList.empty()) {
            std::cout << "Готов 0/1?\n";
            int x;
            std::cin >> x;
            if (x) {
                ready = true;
                break;
            }
        }
        std::cout << "Выбери корабль:\n";
        for (int i = 0; i < shipList.size(); ++i) {
            std::cout << i << ' ';
            for (int j = 0; j < shipList[i].second; ++j) {
                std::cout << "S";
            }
            std::cout << '\n';
        }
        std::cout << "-1 - Убрать корабль\n";
        int shipIndex;
        read(shipIndex);
        if (shipIndex == -1) {
            std::string s;
            read(s);
            game.removeShip(userIndex, {s});
            continue;
        }
        std::string s, t;
        read(s);
        read(t);
        game.setShip(userIndex, shipList[shipIndex].first, {s}, {t});
    }
}

template<typename T>
void ConsoleInterface::read(T& object) {
    std::cin >> object;
    while (!std::cin) {
        std::cin.clear();
        std::cin.ignore(100, '\n');
        Error_command("Invalid input! Try again: \n").execute();
        std::cin >> object;
    }
}

void ConsoleInterface::startConsoleGame() {
    int input = -1;
    while (input != 0) {
        std::cout <<
                  "1. Регистрация\n" <<
                  "2. Начать игру\n" <<
                  "3. Таблица рекордов\n" <<
                  "0. Выход\n";
        read(input);
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
    read(name);
    std::cout << "Введи пароль:\n";
    read(password);
    system->register_new_player(name, password);
}

void ConsoleInterface::newGame() {
    GameSession gameSession(*system);
    for (int gamerIndex = 0; gamerIndex < gameSession.getNumberOfPlayers(); ++gamerIndex) {
        prepareUser(gameSession, gamerIndex);
    }
    while (gameSession.getWinner() == -1) {
        int playerIndex = gameSession.getCurrentPlayer();
        PlayerData data = gameSession.getPlayerData(playerIndex);
        std::string nick = data.getNickName();
        std::string name, password;
        do {
            std::cout << "Вводи пароль снова, " + nick + "\n";
            read(password);
        } while (!system->login(gameSession.getGamerName(playerIndex), password));
        while (gameSession.getCurrentPlayer() == playerIndex && gameSession.getWinner() == -1) {
            for (int i = 0; i < gameSession.getNumberOfPlayers(); ++i) {
                std::cout << "Доска игрока " << gameSession.getPlayerData(i).getNickName() << '\n';
                printField(gameSession, playerIndex, i);
                std::cout << '\n';
            }
            std::cout << "Выбирай клетку для атаки:\n";
            std::string s;
            read(s);
            int nextPlayerIndex = (playerIndex + 1) % gameSession.getNumberOfPlayers();
            gameSession.bomb(playerIndex, nextPlayerIndex, {s});
        }
    }
}

void ConsoleInterface::printLeaderBoard() {
    auto vector = system->getLeaderScore();
    for (auto pair: vector) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
}
