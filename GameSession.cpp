#include "GameSession.h"

bool GameSession::allGamersAreReady() {
    for (auto currentGamerReady: gamerReady) {
        if (!currentGamerReady) {
            return false;
        }
    }
    return true;
}

void GameSession::login(int gamerIndex, const std::string& name, const std::string& password) {
    if (allGamersAreReady()) {
        ErrorCommand("Error the game is already running\n").execute();
        return;
    }
    if (system->login(name, password)) {
        gamer[gamerIndex] = system->getPlayerData(name, password);
        gamerName[gamerIndex] = name;
        gamerLogged[gamerIndex] = true;
    }
}

void GameSession::assertIndex(int gamerIndex) const {
    if (gamerIndex != currentMove) {
        ErrorCommand("It's not your turn\n");
    }
}

void GameSession::nextMove() {
    ++currentMove;
    currentMove %= NUMBER_OF_PLAYERS;
}

void GameSession::setShip(int gamerIndex, int shipIndex, Coordinates begin, Coordinates end) {
    board[gamerIndex].setShip(shipIndex, begin, end);
}

void GameSession::removeShip(int gamerIndex, Coordinates c) {
    board[gamerIndex].removeShip(c);
}

void GameSession::ready(int gamerIndex) {
    if (!board[gamerIndex].isAllShipsSetted()) {
        ErrorCommand("Error. Not all ships set!\n").execute();
        return;
    }
    gamerReady[gamerIndex] = true;
}

void GameSession::bomb(int gamerIndex, int otherGamerIndex, Coordinates c) {
    assertIndex(gamerIndex);
    assertGameEnd();
    if (gamerIndex == otherGamerIndex) {
        ErrorCommand("Error, You can't bomb your sea!\n").execute();
        return;
    }
    Square& square = board[otherGamerIndex].getSquare(c);
    square.bomb();
    if (!square.getShipped()) {
        SayCommand("Мимо!\n").execute();
        nextMove();
        return;
    }
    square.setState('b');
    for (int i = std::max(0, c.x - 1); i < std::min(Board::getN(), c.x + 2); ++i) {
        for (int j = std::max(0, c.y - 1); j < std::min(Board::getM(), c.y + 2); ++j) {
            if (i == c.x || j == c.y) {
                continue;
            }
            board[otherGamerIndex].getSquare({i, j}).setState('!');
        }
    }
    square.setState('x');
    SayCommand(square.getShip()->getHealth() == 0 ? "Убил\n" : "Ранил\n").execute();
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

void GameSession::assertGameEnd() const {
    if (theWinner != -1) {
        ErrorCommand("Error, game has ended!\n").execute();
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

int GameSession::getCurrentPlayer() const {
    return currentMove;
}

PlayerData GameSession::getPlayerData(int playerIndex) {
    return gamer[playerIndex];
}

int GameSession::getWinner() const {
    return theWinner;
}

std::string GameSession::getGamerName(int gamerIndex) {
    return gamerName[gamerIndex];
}

GameSession::GameSession(RegistrationSystem& system) : system(&system) {}
