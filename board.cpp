#include "board.h"

bool Board::isCeilFree(Coordinates c) {return !board[c.x][c.y].getShipped();}
Board::Board(){}
