/**
 * @file ConsoleView.h
 * @brief Header for the ConsoleView class.
 *
 * Handles printing the game state to the standard terminal output.
 */

#ifndef CONSOLEVIEW_H_
#define CONSOLEVIEW_H_

#include "Board.h"

/**
 * @class ConsoleView
 * @brief The 'painter' of the board.
 *
 * It takes a Board and renders a text visualization.
 * Symbols used: '~' is water, '#' is a ship, 'O' is a hit ship, and '^' is a
 * miss.
 */
class ConsoleView {
private:
  Board *board; ///< The board we are currently visualizing

public:
  /**
   * @brief Connect the view to a specific board.
   */
  ConsoleView(Board *board);

  /**
   * @brief Draw the entire board (own grid and opponent tracker) to the
   * console.
   */
  void print();
};

#endif /* CONSOLEVIEW_H_ */
