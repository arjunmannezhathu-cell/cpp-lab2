/**
 * @file OwnGrid.cpp
 * @brief Implementation of the OwnGrid class.
 *
 * This file handles your side of the board: placing your fleet and
 * recording where the opponent has attacked you.
 */

#include "OwnGrid.h"

/**
 * Default Constructor.
 * Sets default 10x10 size.
 */
OwnGrid::OwnGrid() {
  this->rows = 0;
  this->columns = 0;
}

/**
 * Creates the grid and sets the initial fleet limits.
 * Default rules: 1x Carrier(5), 2x Battleships(4), 3x Destroyers(3), 4x
 * Submarines(2).
 */
OwnGrid::OwnGrid(int rows, int columns) {
  this->rows = rows;
  this->columns = columns;

  availableShips[5] = 1;
  availableShips[4] = 2;
  availableShips[3] = 3;
  availableShips[2] = 4;
}

int OwnGrid::getRows() const { return rows; }

int OwnGrid::getColumns() const { return columns; }

/**
 * The logic for placing a ship on the grid.
 * It checks a lot of rules to make sure the placement is legal.
 */
bool OwnGrid::placeShip(const Ship &ship) {
  // 1. Is the ship even valid (straight, right size)?
  if (!ship.isValid()) {
    return false;
  }

  // 2. Do we have any of this type of ship left to place?
  int shipLength = ship.length();
  std::map<int, int>::iterator countIt = availableShips.find(shipLength);

  if (countIt == availableShips.end() || countIt->second <= 0) {
    return false;
  }

  std::set<GridPosition> newShipArea = ship.occupiedArea();

  // 3. Does it fit within the board's dimensions?
  for (std::set<GridPosition>::const_iterator posIt = newShipArea.begin();
       posIt != newShipArea.end(); ++posIt) {
    const GridPosition &currentPos = *posIt;

    char maxRow = 'A' + rows - 1;
    if (currentPos.getRow() < 'A' || currentPos.getRow() > maxRow) {
      return false; // Row out of bounds
    }

    if (currentPos.getColumn() < 1 || currentPos.getColumn() > columns) {
      return false; // Column out of bounds
    }
  }

  // 4. Does it touch or overlap any existing ships?
  // We check against the 'blockedArea' of all currently placed ships.
  for (std::vector<Ship>::const_iterator shipIt = ships.begin();
       shipIt != ships.end(); ++shipIt) {
    const Ship &existingShip = *shipIt;
    std::set<GridPosition> blockedArea = existingShip.blockedArea();

    for (std::set<GridPosition>::const_iterator posIt = newShipArea.begin();
         posIt != newShipArea.end(); ++posIt) {
      if (blockedArea.count(*posIt) > 0) {
        return false; // Too close to another ship!
      }
    }
  }

  // If we got here, the placement is legal!
  ships.push_back(ship);
  availableShips[shipLength]--; // Use up one from our 'inventory'

  return true;
}

std::vector<Ship> OwnGrid::getShips() const { return ships; }

/**
 * Handles what happens when a shot lands on your grid.
 * It records the shot and checks if it hit or sank anything.
 */
Shot::Impact OwnGrid::takeBlow(const Shot &shot) {
  GridPosition target = shot.getTargetPosition();
  shotAt.insert(target); // Record where they shot

  // we look through our fleet to see if they hit anything
  for (std::vector<Ship>::const_iterator shipIt = ships.begin();
       shipIt != ships.end(); ++shipIt) {
    const Ship &ship = *shipIt;
    std::set<GridPosition> occupied = ship.occupiedArea();

    if (occupied.count(target) > 0) {
      // shot hit a ship. Now we check if that whole ship is now destroyed.
      int hitCount = 0; // Count of hits on this ship

      // here we count how many hits we have on this ship
      for (std::set<GridPosition>::const_iterator posIt = occupied.begin();
           posIt != occupied.end(); ++posIt) {
        if (shotAt.count(*posIt) > 0) {
          hitCount++;
        }
      }
      // If all the cells are hits, the ship is sunk
      if (hitCount == ship.length()) {
        return Shot::SUNKEN;
      } else {
        return Shot::HIT;
      }
    }
  }

  // return miss
  return Shot::NONE;
}

const std::set<GridPosition> &OwnGrid::getShotAt() const { return shotAt; }
