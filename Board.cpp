/**
 * @file Board.cpp
 * @brief Implementation of the Board class.
 *
 * This file sets up the complete board by initializing both the
 * player's grid and the opponent's tracker grid.
 */

#include "Board.h"

/**
 * Creates a board of a certain size. In most cases, this will be 10x10.
 */
Board::Board(int rows, int columns) {
  this->ownGrid = OwnGrid(rows, columns);
  this->opponentGrid = OpponentGrid(rows, columns);
}

int Board::getRows() const { return ownGrid.getRows(); }

int Board::getColumns() const { return ownGrid.getColumns(); }

OwnGrid &Board::getOwnGrid() { return ownGrid; }

OpponentGrid &Board::getOpponentGrid() { return opponentGrid; }
