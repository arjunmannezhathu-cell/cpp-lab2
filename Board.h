/**
 * @file Board.h
 * @brief Header for the Board class.
 *
 * The Board is the container that holds both the OwnGrid (your ships)
 * and the OpponentGrid (your tracker).
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "OpponentGrid.h"
#include "OwnGrid.h"

/**
 * @class Board
 * @brief Represents a player's entire view of the game.
 *
 * Every player has one Board. It contains their own fleet and their
 * knowledge of the enemy's fleet.
 */
class Board {
private:
  OwnGrid ownGrid;           ///< Where our ships are placed
  OpponentGrid opponentGrid; ///< Where we track our attacks on the enemy

public:
  /**
   * @brief Create a new game board.
   * @param rows Height of the board.
   * @param columns Width of the board.
   */
  Board(int rows, int columns);

  /**
   * @brief Get height of the game area.
   */
  int getRows() const;

  /**
   * @brief Get width of the game area.
   */
  int getColumns() const;

  /**
   * @brief Get access to our own fleet grid.
   */
  OwnGrid &getOwnGrid();

  /**
   * @brief Get access to our record of the opponent's board.
   */
  OpponentGrid &getOpponentGrid();
};

#endif /* BOARD_H_ */
