/**
 * @file Shot.h
 * @brief Header for the Shot class.
 *
 * Defines what a shot is and the possible outcomes when it hits a grid.
 */

#ifndef SHOT_H_
#define SHOT_H_

#include "GridPosition.h"

/**
 * @class Shot
 * @brief Represents a single attack on a grid square.
 */
class Shot {
public:
  /**
   * @brief The possible results of an attack.
   */
  enum Impact {
    NONE,  ///< The shot hit water (Miss)
    HIT,   ///< The shot hit a ship segment
    SUNKEN ///< The shot hit the final segment, destroying the ship
  };

private:
  GridPosition targetPosition; ///< The target coordinate

public:
  /**
   * @brief Create a shot at a specific position.
   */
  Shot(GridPosition targetPosition);

  /**
   * @brief Get the location being attacked.
   */
  GridPosition getTargetPosition() const;
};

#endif /* SHOT_H_ */
