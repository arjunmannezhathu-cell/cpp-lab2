/**
 * @file Shot.cpp
 * @brief Implementation of the Shot class.
 */

#include "Shot.h"

/**
 * Creates a shot aimed at a specific coordinate.
 */
Shot::Shot(GridPosition targetPosition) : targetPosition(targetPosition) {}

GridPosition Shot::getTargetPosition() const { return targetPosition; }
