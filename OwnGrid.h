/**
 * @file OwnGrid.h
 * @brief Player's own grid for ship placement
 */

#ifndef OWNGRID_H_
#define OWNGRID_H_

#include "Ship.h"
#include "Shot.h"
#include <map>
#include <set>
#include <vector>

/**
 * @brief The player's own grid
 *
 * Used to place ships and track incoming shots
 */
class OwnGrid {
private:
  /// Number of rows
  int rows;

  /// Number of columns
  int columns;

  /// Ships placed on the grid
  std::vector<Ship> ships;

  /// Positions that have been shot at
  std::set<GridPosition> shotAt;

  /// Available ships: length -> count remaining
  std::map<int, int> availableShips;

public:
  /**
   * @brief Create grid with given size
   * @param rows Number of rows
   * @param columns Number of columns
   */
  OwnGrid(int rows, int columns);

  /// @brief Get number of rows
  int getRows() const;

  /// @brief Get number of columns
  int getColumns() const;

  /**
   * @brief Try to place a ship on the grid
   *
   * Checks all placement rules (no touching, count limits, etc)
   * @param ship Ship to place
   * @return true if placed successfully
   */
  bool placeShip(const Ship &ship);

  /// @brief Get all ships on grid
  std::vector<Ship> getShips() const;

  /**
   * @brief Process incoming shot from opponent
   * @param shot The incoming shot
   * @return NONE if miss, HIT if hit, SUNKEN if ship sunk
   */
  Shot::Impact takeBlow(const Shot &shot);

  /// @brief Get all positions shot at
  const std::set<GridPosition> &getShotAt() const;
};

#endif /* OWNGRID_H_ */
