/**
 * @file Ship.cpp
 * @brief Implementation of Ship class
 */

#include "Ship.h"
#include <algorithm>
#include <cstdlib>

Ship::Ship(const GridPosition &bow, const GridPosition &stern)
    : bow(bow), stern(stern) {}

bool Ship::isValid() const {
  // Both positions must be valid
  if (!bow.isValid() || !stern.isValid()) {
    return false;
  }

  // Check horizontal or vertical alignment
  bool isHorizontal = (bow.getRow() == stern.getRow());
  bool isVertical = (bow.getColumn() == stern.getColumn());

  if (!isHorizontal && !isVertical) {
    // Diagonal ships not allowed
    return false;
  }

  // Length must be 2-5
  int shipLength = length();
  if (shipLength < 2 || shipLength > 5) {
    return false;
  }

  return true;
}

GridPosition Ship::getBow() const { return bow; }

GridPosition Ship::getStern() const { return stern; }

int Ship::length() const {
  // Calculate distance between bow and stern
  if (bow.getRow() == stern.getRow()) {
    // Horizontal
    int colDiff = stern.getColumn() - bow.getColumn();
    return std::abs(colDiff) + 1;
  } else {
    // Vertical
    int rowDiff = stern.getRow() - bow.getRow();
    return std::abs(rowDiff) + 1;
  }
}

std::set<GridPosition> Ship::occupiedArea() const {
  std::set<GridPosition> occupied;

  if (bow.getRow() == stern.getRow()) {
    // Horizontal ship - iterate columns
    int startCol = std::min(bow.getColumn(), stern.getColumn());
    int endCol = std::max(bow.getColumn(), stern.getColumn());

    for (int col = startCol; col <= endCol; col++) {
      GridPosition gridPos(bow.getRow(), col);
      occupied.insert(gridPos);
    }
  } else {
    // Vertical ship - iterate rows
    char startRow = std::min(bow.getRow(), stern.getRow());
    char endRow = std::max(bow.getRow(), stern.getRow());

    for (char currentRow = startRow; currentRow <= endRow; currentRow++) {
      GridPosition gridPos(currentRow, bow.getColumn());
      occupied.insert(gridPos);
    }
  }

  return occupied;
}

std::set<GridPosition> Ship::blockedArea() const {
  std::set<GridPosition> blocked;
  std::set<GridPosition> occupied = occupiedArea();

  // For each occupied position, add all 8 neighbors
  for (std::set<GridPosition>::const_iterator occupiedIt = occupied.begin();
       occupiedIt != occupied.end(); ++occupiedIt) {
    const GridPosition &gridPos = *occupiedIt;

    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
      for (int colOffset = -1; colOffset <= 1; colOffset++) {
        char newRow = gridPos.getRow() + rowOffset;
        int newCol = gridPos.getColumn() + colOffset;

        GridPosition neighborPos(newRow, newCol);
        blocked.insert(neighborPos);
      }
    }
  }

  return blocked;
}
