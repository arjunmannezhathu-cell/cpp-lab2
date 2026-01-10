/**
 * @file ConsoleView.h
 * @brief Displays the board on console
 */

#ifndef CONSOLEVIEW_H_
#define CONSOLEVIEW_H_

#include "Board.h"

/**
 * @brief Shows the game state on console
 *
 * Displays both grids side by side
 */
class ConsoleView {
private:
  /// Pointer to the board we display
  Board *board;

public:
  /**
   * @brief Create view for given board
   * @param board Board to display
   */
  ConsoleView(Board *board);

  /**
   * @brief Print both grids to console
   *
   * Symbols: ~ water, # ship, O hit, ^ miss
   */
  void print();
};

#endif /* CONSOLEVIEW_H_ */
