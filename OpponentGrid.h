/**
 * @file OpponentGrid.h
 * @brief Tracks shots at opponent's grid
 */

#ifndef OPPONENTGRID_H_
#define OPPONENTGRID_H_

#include "GridPosition.h"
#include "Ship.h"
#include "Shot.h"
#include <map>
#include <vector>

/**
 * @brief Opponent's grid from our perspective
 *
 * Tracks our shots and deduces sunken ships
 */
class OpponentGrid {
private:
  /// Number of rows
  int rows;

  /// Number of columns
  int columns;

  /// Our shots and their results
  std::map<GridPosition, Shot::Impact> shots;

  /// Ships we've sunk
  std::vector<Ship> sunkenShips;

public:
  /**
   * @brief Create grid with given size
   */
  OpponentGrid(int rows, int columns);

  /// @brief Get number of rows
  int getRows() const;

  /// @brief Get number of columns
  int getColumns() const;

  /**
   * @brief Record result of a shot
   *
   * If SUNKEN, we figure out where the ship was
   * @param shot The shot we fired
   * @param impact What happened (NONE/HIT/SUNKEN)
   */
  void shotResult(const Shot &shot, Shot::Impact impact);

  /// @brief Get all our shots
  const std::map<GridPosition, Shot::Impact> &getShotsAt() const;

  /// @brief Get sunken ships we found
  const std::vector<Ship> &getSunkenShips() const;
};

#endif /* OPPONENTGRID_H_ */
