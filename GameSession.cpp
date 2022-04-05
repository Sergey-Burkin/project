#include "GameSession.h"

bool GameSession::allGamersAreReady() {
    for (auto x: gamerReady) {
        if (!x) {
            return false;
        }
    }
    return true;
}

void GameSession::login(int gamerNumber, const std::string& name, const std::string& password) {
//    assertNumber(gamerNumber);
    if (allGamersAreReady()) {
        Error_command("Error the game is already running\n").execute();
        return;
    }
    if (system->login(name, password)) {
        gamer[gamerNumber] = system->get_player_data(name, password);
    }
}

void GameSession::assertNumber(int gameNumber) {
    if (gameNumber != currentMove) {
        Error_command("It's not your turn\n");
    }
}

void GameSession::nextMove() {
    ++currentMove;
    currentMove %= NUMBER_OF_PLAYERS;
}

void GameSession::setShip(int gameNumber, int shipNumber, Coordinates begin, Coordinates end) {
    board[gameNumber].setShip(shipNumber, begin, end);
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
    assertNumber(gamerIndex);
    assertGameEnd();
    if (gamerIndex == otherGamerIndex) {
        Error_command("Error, You can't bomb your sea!\n").execute();
        return;
    }
    auto currentCeil = board[otherGamerIndex].getCeil(c);
    currentCeil.bomb();
    if (!currentCeil.getShipped()) {
        SayCommand("Мимо!\n").execute();
        nextMove();
        return;
    }
    for (int i = std::max(0, c.x - 1); i < std::min(board[otherGamerIndex].getN(), c.x + 1); ++i) {
        for (int j = std::max(0, c.y - 1); j < std::min(board[otherGamerIndex].getM(), c.y + 1); ++j) {
            if (i == c.x || j == c.y ) {
                continue;
            }
            board[otherGamerIndex].getCeil(Coordinates(i, j)).setState('!');
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
        if (winner) {
            SayCommand("И победитель " + gamer[index].getNickName() + "!\n");
            theWinner = gamerIndex;
        }
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
