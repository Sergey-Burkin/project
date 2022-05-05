#include "ConsoleInterface.h"

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
    while (!(shipIndex >= -1 && 0 < list.size() - shipIndex)) {
        std::cout << "Выберите корабль:\n";
        for (int i = 0; i < list.size(); ++i) {
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

Coordinates ConsoleInterface::askForSquare() {
    std::cout << "Укажите клетку (например, A5)\n";
    std::string s;
    read(s);
    return {s};
}

void ConsoleInterface::showMenu() {
    std::cout <<
              "1. Регистрация\n" <<
              "2. Начать игру\n" <<
              "3. Таблица рекордов\n" <<
              "0. Выход\n";
}


void ConsoleInterface::prepareUser(GameSession& game, int userIndex) {
    while (!game.getLogged(userIndex)) {
        std::string name, password;
        askForLogin(userIndex, name, password);
        LogInCommand(&game, userIndex, name, password).execute();
    }
    while (true) {
        printField(game, userIndex, userIndex);
        auto shipList = game.getFreeShips(userIndex);
        if (shipList.empty()) {
            bool ready = askIfReady();
            if (ready) {
                game.ready(userIndex);
                break;
            }
        }

        int shipIndex = askForShip(shipList);
        if (shipIndex == -1) {
            game.removeShip(userIndex, askForSquare());
            continue;
        }
        SayCommand("Выберете две крайние клетки для корабля\n").execute();
        game.setShip(userIndex, shipList[shipIndex].first, askForSquare(), askForSquare());
    }
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
        printField(game, playerIndex, i);
        std::cout << '\n';
    }
}

void ConsoleInterface::relogin(const std::string& nick, std::string& password) {
    SayCommand("Введте пароль снова, " + nick + "\n").execute();
    read(password);
}

void ConsoleInterface::startConsoleGame() {
    int input = -1;
    while (input != 0) {
        showMenu();
        input = getOption();
        if (input == 1) {
            registerPlayer();
        } else if (input == 2) {
            newGame();
        } else if (input == 3) {
            showLeaderBoard();
        }
    }
}

void ConsoleInterface::registerPlayer() {
    std::string name, password;
    askRegister(name, password);
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
            relogin(nick, password);
        } while (!system->login(gameSession.getGamerName(playerIndex), password));
        while (gameSession.getCurrentPlayer() == playerIndex && gameSession.getWinner() == -1) {
            showAllBoards(gameSession, playerIndex);
            SayCommand("Выбирай клетку для атаки:\n").execute();
            int nextPlayerIndex = (playerIndex + 1) % gameSession.getNumberOfPlayers();
            gameSession.bomb(playerIndex, nextPlayerIndex, askForSquare());
        }
    }
}

void ConsoleInterface::showLeaderBoard() {
    auto vector = system->getLeaderScore();
    for (auto& pair: vector) {
        std::cout << pair.first << ' ' << pair.second << '\n';
    }
}
