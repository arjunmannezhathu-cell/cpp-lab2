/**
 * @file Board.h
 * @brief Main game board combining both grids
 */

#ifndef BOARD_H_
#define BOARD_H_

#include "OpponentGrid.h"
#include "OwnGrid.h"

/**
 * @brief The game board from one player's view
 *
 * Has our grid (with ships) and opponent grid (for tracking shots)
 */
class Board {
private:
  /// Our ships go here
  OwnGrid ownGrid;

  /// Track shots at opponent
  OpponentGrid opponentGrid;

public:
  /**
   * @brief Create board with given size
   */
  Board(int rows, int columns);

  /// @brief Get number of rows
  int getRows() const;

  /// @brief Get number of columns
  int getColumns() const;

  /// @brief Get our grid
  OwnGrid &getOwnGrid();

  /// @brief Get opponent grid
  OpponentGrid &getOpponentGrid();
};

#endif /* BOARD_H_ */
