/**
 * @file Ship.cpp
 * @brief Implementation of the Ship class.
 *
 * This file handles how ships are defined, validated, and how they
 * occupy space on the grid.
 */

#include "Ship.h"
#include <algorithm>
#include <cstdlib>

/**
 * Creates a ship by defining its two endpoints (the bow and the stern).
 */
Ship::Ship(const GridPosition &bow, const GridPosition &stern) {
  this->bow = bow;
  this->stern = stern;
}

/**
 * Checks if a ship is built correctly according to the rules:
 * 1. Both ends must be on the board.
 * 2. It must be either perfectly horizontal or perfectly vertical.
 * 3. It must be between 2 and 5 segments long.
 */
bool Ship::isValid() const {
  if (!bow.isValid() || !stern.isValid()) {
    return false;
  }

  bool isHorizontal = (bow.getRow() == stern.getRow());
  bool isVertical = (bow.getColumn() == stern.getColumn());

  if (!isHorizontal && !isVertical) {
    // No diagonal ships in this game!
    return false;
  }

  int shipLength = length();
  if (shipLength < 2 || shipLength > 5) {
    // Only ships of size 2, 3, 4, or 5 are allowed.
    return false;
  }

  return true;
}

GridPosition Ship::getBow() const { return bow; }

GridPosition Ship::getStern() const { return stern; }

/**
 * Calculates how many squares the ship covers.
 * We subtract coordinates and add 1 (since both ends count).
 */
int Ship::length() const {
  if (bow.getRow() == stern.getRow()) {
    // Thinking horizontally: difference between columns
    int colDiff = stern.getColumn() - bow.getColumn();
    return std::abs(colDiff) + 1;
  } else {
    // Thinking vertically: difference between rows
    int rowDiff = stern.getRow() - bow.getRow();
    return std::abs(rowDiff) + 1;
  }
}

/**
 * Returns a set of every individual square the ship physically occupies.
 */
std::set<GridPosition> Ship::occupiedArea() const {
  std::set<GridPosition> occupied;

  if (bow.getRow() == stern.getRow()) {
    // Loop through the columns from the smaller to the larger coordinate
    int startCol = std::min(bow.getColumn(), stern.getColumn());
    int endCol = std::max(bow.getColumn(), stern.getColumn());

    for (int col = startCol; col <= endCol; col++) {
      occupied.insert(GridPosition(bow.getRow(), col));
    }
  } else {
    // Loop through the rows from the 'smaller' to the 'larger' letter
    char startRow = std::min(bow.getRow(), stern.getRow());
    char endRow = std::max(bow.getRow(), stern.getRow());

    for (char currentRow = startRow; currentRow <= endRow; currentRow++) {
      occupied.insert(GridPosition(currentRow, bow.getColumn()));
    }
  }

  return occupied;
}

/**
 * Returns the ship's occupied area PLUS all the squares right next to it.
 * This is used to make sure ships don't touch each other.
 */
std::set<GridPosition> Ship::blockedArea() const {
  std::set<GridPosition> blocked;
  std::set<GridPosition> occupied = occupiedArea();

  // For every single square of the ship, we 'look' at all 8 neighbors
  for (std::set<GridPosition>::const_iterator occupiedIt = occupied.begin();
       occupiedIt != occupied.end(); ++occupiedIt) {
    const GridPosition &gridPos = *occupiedIt;

    // Use a nested loop to check offsets of -1, 0, and +1 for both row and col
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
      for (int colOffset = -1; colOffset <= 1; colOffset++) {
        char newRow = gridPos.getRow() + rowOffset;
        int newCol = gridPos.getColumn() + colOffset;

        // We don't worry about being 'out of bounds' here,
        // because the GridPosition constructor handles safe/invalid values.
        blocked.insert(GridPosition(newRow, newCol));
      }
    }
  }

  return blocked;
}
