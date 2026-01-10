/**
 * @file Board.cpp
 * @brief Implementation of Board class
 */

#include "Board.h"

Board::Board(int rows, int columns)
    : ownGrid(rows, columns), opponentGrid(rows, columns) {}

int Board::getRows() const { return ownGrid.getRows(); }

int Board::getColumns() const { return ownGrid.getColumns(); }

OwnGrid &Board::getOwnGrid() { return ownGrid; }

OpponentGrid &Board::getOpponentGrid() { return opponentGrid; }
