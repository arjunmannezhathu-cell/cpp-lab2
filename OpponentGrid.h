/**
 * @file OpponentGrid.h
 * @brief Header for the OpponentGrid class.
 *
 * This class tracks what we know about the opponent's board based
 * on the shots we've fired.
 */

#ifndef OPPONENTGRID_H_
#define OPPONENTGRID_H_

#include "GridPosition.h"
#include "Ship.h"
#include "Shot.h"
#include <map>
#include <vector>

/**
 * @class OpponentGrid
 * @brief Represents the opponent's side of the game.
 *
 * Since we can't see their ships, we record 'HIT' or 'MISS' for every square
 * we attack. When we sink a ship, we try to reconstruct its full position.
 */
class OpponentGrid {
private:
  int rows;    ///< Height of the grid
  int columns; ///< Width of the grid

  std::map<GridPosition, Shot::Impact> shots; ///< History of our attacks
  std::vector<Ship> sunkenShips; ///< Ships we've successfully destroyed

public:
  /**
   * @brief Create a grid to track an opponent of a certain size.
   */
  OpponentGrid(int rows, int columns);

  /**
   * @brief Get height of the board.
   */
  int getRows() const;

  /**
   * @brief Get width of the board.
   */
  int getColumns() const;

  /**
   * @brief Call this after firing a shot to record what happened.
   * @param shot The shot we fired.
   * @param impact The result (NONE, HIT, or SUNKEN).
   */
  void shotResult(const Shot &shot, Shot::Impact impact);

  /**
   * @brief Get all shots we've fired so far.
   */
  const std::map<GridPosition, Shot::Impact> &getShotsAt() const;

  /**
   * @brief Get the list of all opponent ships we've sunk.
   */
  const std::vector<Ship> &getSunkenShips() const;
};

#endif /* OPPONENTGRID_H_ */
