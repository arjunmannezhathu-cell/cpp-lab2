/**
 * @file Shot.h
 * @brief Represents a shot in the game
 */

#ifndef SHOT_H_
#define SHOT_H_

#include "GridPosition.h"

/**
 * @brief A shot at a grid position
 */
class Shot {
public:
  /**
   * @brief Result of a shot
   */
  enum Impact {
    NONE,  ///< Missed
    HIT,   ///< Hit but not sunk
    SUNKEN ///< Ship sunk
  };

private:
  /// Where the shot was aimed
  GridPosition targetPosition;

public:
  /**
   * @brief Create a shot at given position
   * @param targetPosition Where to shoot
   */
  Shot(GridPosition targetPosition);

  /// @brief Get the target position
  GridPosition getTargetPosition() const;
};

#endif /* SHOT_H_ */
