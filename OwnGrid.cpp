/**
 * @file OwnGrid.cpp
 * @brief Implementation of OwnGrid class
 */

#include "OwnGrid.h"

OwnGrid::OwnGrid(int rows, int columns) : rows(rows), columns(columns) {
  // Initialize ship counts
  // 1x Carrier (5), 2x Battleship (4), 3x Destroyer (3), 4x Submarine (2)
  availableShips[5] = 1;
  availableShips[4] = 2;
  availableShips[3] = 3;
  availableShips[2] = 4;
}

int OwnGrid::getRows() const { return rows; }

int OwnGrid::getColumns() const { return columns; }

bool OwnGrid::placeShip(const Ship &ship) {
  // Check if ship itself is valid
  if (!ship.isValid()) {
    return false;
  }

  // Check if we can still place this length
  int shipLength = ship.length();
  std::map<int, int>::iterator countIt = availableShips.find(shipLength);

  if (countIt == availableShips.end() || countIt->second <= 0) {
    return false;
  }

  std::set<GridPosition> newShipArea = ship.occupiedArea();

  // Check bounds
  for (std::set<GridPosition>::const_iterator posIt = newShipArea.begin();
       posIt != newShipArea.end(); ++posIt) {
    const GridPosition &currentPos = *posIt;

    char maxRow = 'A' + rows - 1;
    if (currentPos.getRow() < 'A' || currentPos.getRow() > maxRow) {
      return false;
    }

    if (currentPos.getColumn() < 1 || currentPos.getColumn() > columns) {
      return false;
    }
  }

  // Check if ship touches any existing ship
  for (std::vector<Ship>::const_iterator shipIt = ships.begin();
       shipIt != ships.end(); ++shipIt) {
    const Ship &existingShip = *shipIt;
    std::set<GridPosition> blockedArea = existingShip.blockedArea();

    for (std::set<GridPosition>::const_iterator posIt = newShipArea.begin();
         posIt != newShipArea.end(); ++posIt) {
      if (blockedArea.count(*posIt) > 0) {
        return false;
      }
    }
  }

  // All checks passed - add the ship
  ships.push_back(ship);
  availableShips[shipLength]--;

  return true;
}

std::vector<Ship> OwnGrid::getShips() const { return ships; }

Shot::Impact OwnGrid::takeBlow(const Shot &shot) {
  GridPosition target = shot.getTargetPosition();
  shotAt.insert(target);

  // Check each ship for hit
  for (std::vector<Ship>::const_iterator shipIt = ships.begin();
       shipIt != ships.end(); ++shipIt) {
    const Ship &ship = *shipIt;
    std::set<GridPosition> occupied = ship.occupiedArea();

    if (occupied.count(target) > 0) {
      // Hit! Check if ship is sunk
      int hitCount = 0;

      for (std::set<GridPosition>::const_iterator posIt = occupied.begin();
           posIt != occupied.end(); ++posIt) {
        if (shotAt.count(*posIt) > 0) {
          hitCount++;
        }
      }

      if (hitCount == ship.length()) {
        return Shot::SUNKEN;
      } else {
        return Shot::HIT;
      }
    }
  }

  return Shot::NONE;
}

const std::set<GridPosition> &OwnGrid::getShotAt() const { return shotAt; }
