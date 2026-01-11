/**
 * @file Board.cpp
 * @brief Implementation of the Board class.
 *
 * This is the board file. It sets up the complete board by initializing both
 * the player's grid and the opponent's tracker grid.
 */

#include "Board.h"

/**
 * Creates a board of a certain size.
 */
Board::Board(int rows, int columns) {
  this->ownGrid = OwnGrid(rows, columns);
  this->opponentGrid = OpponentGrid(rows, columns);
}

/**
 * Returns the number of rows in the board.
 */
int Board::getRows() const { return ownGrid.getRows(); }

/**
 * Returns the number of columns in the board.
 */
int Board::getColumns() const { return ownGrid.getColumns(); }

/**
 * Returns a reference to the player's grid.
 */
OwnGrid &Board::getOwnGrid() { return ownGrid; }

/**
 * Returns a reference to the opponent's grid.
 */
OpponentGrid &Board::getOpponentGrid() { return opponentGrid; }
