/**
 * @file Ship.h
 * @brief Header for the Ship class.
 *
 * Defines what a ship is (bow and stern positions) and the rules for
 * how it occupies space.
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "GridPosition.h"
#include <set>

/**
 * @class Ship
 * @brief Represents a single ship on the grid.
 *
 * Ships are immutable. A ship knows its occupied area (the squares it covers)
 * and its blocked area (occupied area plus a 1-square buffer).
 */
class Ship {
private:
  GridPosition bow;   ///< Start coordinate
  GridPosition stern; ///< End coordinate

public:
  /**
   * @brief Create a ship from a bow and stern position.
   */
  Ship(const GridPosition &bow, const GridPosition &stern);

  /**
   * @brief Check if the ship follows the placement rules (straight, valid
   * size).
   */
  bool isValid() const;

  /**
   * @brief Get the bow (start) position.
   */
  GridPosition getBow() const;

  /**
   * @brief Get the stern (end) position.
   */
  GridPosition getStern() const;

  /**
   * @brief Calculate how many squares the ship is long.
   */
  int length() const;

  /**
   * @brief Get every single coordinate the ship physically covers.
   */
  std::set<GridPosition> occupiedArea() const;

  /**
   * @brief Get the ship's area plus all surrounding neighbor squares.
   */
  std::set<GridPosition> blockedArea() const;
};

#endif /* SHIP_H_ */
