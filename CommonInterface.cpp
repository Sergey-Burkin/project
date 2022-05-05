#include "CommonInterface.h"


void CommonInterface::prepareUser(GameSession& game, int userIndex) {
    while (!game.getLogged(userIndex)) {
        std::string name, password;
        askForLogin(userIndex, name, password);
        LogInCommand(&game, userIndex, name, password).execute();
    }
    while (true) {
        showField(game, userIndex, userIndex);
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

void CommonInterface::registerPlayer() {
    std::string name, password;
    askRegister(name, password);
    system->registerNewPlayer(name, password);
}

void CommonInterface::newGame() {
    if (system->getNumberOfUsers() == 0) {
        ErrorCommand("Nobody registered!\n").execute();
        return;
    }
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
            loginAgain(nick, password);
        } while (!system->login(gameSession.getGamerName(playerIndex), password));
        while (gameSession.getCurrentPlayer() == playerIndex && gameSession.getWinner() == -1) {
            showAllBoards(gameSession, playerIndex);
            SayCommand("Выбирай клетку для атаки:\n").execute();
            int nextPlayerIndex = (playerIndex + 1) % gameSession.getNumberOfPlayers();
            gameSession.bomb(playerIndex, nextPlayerIndex, askForSquare());
        }
    }
}

void CommonInterface::startGame() {
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
