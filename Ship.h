/**
 * @file Ship.h
 * @brief Represents a ship in the battleship game
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "GridPosition.h"
#include <set>

/**
 * @brief A ship on the grid with bow and stern positions
 *
 * Immutable - position can't change after creation
 */
class Ship {
private:
  /// Front of the ship
  GridPosition bow;

  /// Back of the ship
  GridPosition stern;

public:
  /**
   * @brief Create a ship from bow to stern
   * @param bow Front position
   * @param stern Back position
   */
  Ship(const GridPosition &bow, const GridPosition &stern);

  /**
   * @brief Check if ship is valid
   * Must be horizontal/vertical, length 2-5
   */
  bool isValid() const;

  /// @brief Get bow position
  GridPosition getBow() const;

  /// @brief Get stern position
  GridPosition getStern() const;

  /// @brief Calculate length of ship
  int length() const;

  /**
   * @brief Get all positions this ship occupies
   * @return Set of grid positions
   */
  std::set<GridPosition> occupiedArea() const;

  /**
   * @brief Get occupied area plus surrounding positions
   * Used to check if ships touch each other
   */
  std::set<GridPosition> blockedArea() const;
};

#endif /* SHIP_H_ */
