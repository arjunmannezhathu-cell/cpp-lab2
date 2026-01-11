/**
 * @file OwnGrid.h
 * @brief Header for the OwnGrid class.
 *
 * Manages the player's own grid, including ship placement and
 * recording incoming shots.
 */

#ifndef OWNGRID_H_
#define OWNGRID_H_

#include "Ship.h"
#include "Shot.h"
#include <map>
#include <set>
#include <vector>

/**
 * @class OwnGrid
 * @brief Represents your side of the board.
 *
 * Tracks your ships and where you've been hit. It enforces rules
 * for ship placement.
 */
class OwnGrid {
private:
  int rows;    ///< Total rows (usually 10)
  int columns; ///< Total columns (usually 10)

  std::vector<Ship> ships;           ///< Our placed fleet
  std::set<GridPosition> shotAt;     ///< Where the opponent shot us
  std::map<int, int> availableShips; ///< How many of each ship type are left

public:
  /**
   * @brief Default Constructor.
   */
  OwnGrid();

  /**
   * @brief Create a grid with specific dimensions.
   */
  OwnGrid(int rows, int columns);

  /**
   * @brief Get height of the board.
   */
  int getRows() const;

  /**
   * @brief Get width of the board.
   */
  int getColumns() const;

  /**
   * @brief Try to place a ship on the board.
   * @return True if placement was legal and successful.
   */
  bool placeShip(const Ship &ship);

  /**
   * @brief Get the list of all our placed ships.
   */
  std::vector<Ship> getShips() const;

  /**
   * @brief Process a shot from the opponent.
   * @return NONE, HIT, or SUNKEN.
   */
  Shot::Impact takeBlow(const Shot &shot);

  /**
   * @brief Get the set of all coordinates where the opponent shot us.
   */
  const std::set<GridPosition> &getShotAt() const;
};

#endif /* OWNGRID_H_ */
