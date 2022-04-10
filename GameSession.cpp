#include "GameSession.h"

bool GameSession::allGamersAreReady() {
    for (auto x: gamerReady) {
        if (!x) {
            return false;
        }
    }
    return true;
}

void GameSession::login(int gamerIndex, const std::string& name, const std::string& password) {
//    assertIndex(gamerIndex);
    if (allGamersAreReady()) {
        Error_command("Error the game is already running\n").execute();
        return;
    }
    if (system->login(name, password)) {
        gamer[gamerIndex] = system->get_player_data(name, password);
        gamerName[gamerIndex] = name;
        gamerLogged[gamerIndex] = true;
    }
}

void GameSession::assertIndex(int gamerIndex) {
    if (gamerIndex != currentMove) {
        Error_command("It's not your turn\n");
    }
}

void GameSession::nextMove() {
    ++currentMove;
    currentMove %= NUMBER_OF_PLAYERS;
}

void GameSession::setShip(int gamerIndex, int shipIndex, Coordinates begin, Coordinates end) {
    board[gamerIndex].setShip(shipIndex, begin, end);
}

void GameSession::removeShip(int gamerIndex, int shipIndex) {
    board[gamerIndex].removeShip(shipIndex);
}

void GameSession::removeShip(int gamerIndex, Coordinates c) {
    board[gamerIndex].removeShip(c);
}

void GameSession::ready(int gamerIndex) {
    if (!board[gamerIndex].isAllShipsSetted()) {
        Error_command("Error. Not all ships set!\n").execute();
        return;
    }
    gamerReady[gamerIndex] = true;
}

void GameSession::bomb(int gamerIndex, int otherGamerIndex, Coordinates c) {
    assertIndex(gamerIndex);
    assertGameEnd();
    if (gamerIndex == otherGamerIndex) {
        Error_command("Error, You can't bomb your sea!\n").execute();
        return;
    }
    Ceil& currentCeil = board[otherGamerIndex].getCeil(c);
    currentCeil.bomb();
    if (!currentCeil.getShipped()) {
        SayCommand("Мимо!\n").execute();
        nextMove();
        return;
    }
    currentCeil.setState('b');
    for (int i = std::max(0, c.x - 1); i < std::min(board[otherGamerIndex].getN(), c.x + 1); ++i) {
        for (int j = std::max(0, c.y - 1); j < std::min(board[otherGamerIndex].getM(), c.y + 1); ++j) {
            if (i == c.x || j == c.y ) {
                continue;
            }
            board[otherGamerIndex].getCeil({i, j}).setState('!');
        }
    }
    SayCommand(currentCeil.getShip()->getHealth() == 0 ? "Убил\n" : "Ранил\n").execute();
    bool winner = true;
    for (int index = 0; index < NUMBER_OF_PLAYERS; ++index) {
        if (index == gamerIndex) {
            continue;
        }
        if (board[index].getHealth() != 0) {
            winner = false;
        }
    }
    if (winner) {
        SayCommand("И победитель " + gamer[gamerIndex].getNickName() + "!\n").execute();
        theWinner = gamerIndex;
        system->addPlayerScore(gamerName[theWinner], 1);
    }
}

void GameSession::assertGameEnd() {
    if (theWinner != -1) {
        Error_command("Error, game has ended!\n").execute();
    }
}

Mark GameSession::getMark(int gamerIndex, int boardIndex, Coordinates c) {
    return gamerIndex == boardIndex ? board[boardIndex].getOwnMark(c) : board[boardIndex].getOtherMark(c);
}

int GameSession::getBoardHeight(int boardIndex) {
    return board[boardIndex].getN();
}

int GameSession::getBoardWidth(int boardIndex) {
    return board[boardIndex].getM();
}

bool GameSession::getLogged(int gamerIndex) {
    return gamerLogged[gamerIndex];
}

int GameSession::getNumberOfPlayers() {
    return NUMBER_OF_PLAYERS;
}

std::vector<std::pair<int, int>> GameSession::getFreeShips(int gamerIndex) {
    return board[gamerIndex].getUnsettedShipsList();
}

int GameSession::getCurrentPlayer() {
    return currentMove;
}

PlayerData GameSession::getPlayerData(int playerIndex) {
    return gamer[playerIndex];
}

int GameSession::getWinner() {
    return theWinner;
}

std::string GameSession::getGamerName(int gamerIndex) {
    return gamerName[gamerIndex];
}
