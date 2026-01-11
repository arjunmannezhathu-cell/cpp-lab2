/**
 * @file OpponentGrid.cpp
 * @brief Implementation of the OpponentGrid class.
 *
 * This is our 'tracker' grid. We use it to remember where we've shot
 * the opponent and to piece together where their ships were once we sink them.
 */

#include "OpponentGrid.h"
#include <set>

OpponentGrid::OpponentGrid() {
  this->rows = 0;
  this->columns = 0;
}

OpponentGrid::OpponentGrid(int rows, int columns) {
  this->rows = rows;
  this->columns = columns;
}

int OpponentGrid::getRows() const { return rows; }

int OpponentGrid::getColumns() const { return columns; }

/**
 * Records the result of a shot we fired.
 * If we sink a ship, we run a search to find out exactly where
 * that ship was based on our previous 'HIT' records.
 */
void OpponentGrid::shotResult(const Shot &shot, Shot::Impact impact) {
  GridPosition target = shot.getTargetPosition();
  shots[target] = impact;

  // If we just sank a ship, we need to 'find' all its parts!
  if (impact == Shot::SUNKEN) {
    std::set<GridPosition> shipPositions;
    shipPositions.insert(
        target); // The square we just hit is definitely part of it

    char shipRow = target.getRow();   // Row of the ship
    int shipCol = target.getColumn(); // Column of the ship

    bool isHorizontal = false;

    // 1. Look to the LEFT for more hits/sunk markers belonging to this ship
    for (int col = shipCol - 1; col >= 1; col--) {
      GridPosition leftPos(shipRow, col); // Position to the left
      std::map<GridPosition, Shot::Impact>::iterator shotFindIt =
          shots.find(leftPos);

      if (shotFindIt != shots.end() && (shotFindIt->second == Shot::HIT ||
                                        shotFindIt->second == Shot::SUNKEN)) {
        shipPositions.insert(leftPos);
        isHorizontal =
            true; // If we found stuff left or right, it's a horizontal ship
      } else {
        break; // Hit a miss or water, stop looking
      }
    }

    // 2. Look to the RIGHT
    for (int col = shipCol + 1; col <= columns; col++) {
      GridPosition rightPos(shipRow, col);
      std::map<GridPosition, Shot::Impact>::iterator shotFindIt =
          shots.find(rightPos);

      if (shotFindIt != shots.end() && (shotFindIt->second == Shot::HIT ||
                                        shotFindIt->second == Shot::SUNKEN)) {
        shipPositions.insert(rightPos);
        isHorizontal = true;
      } else {
        break;
      }
    }

    // 3. If we didn't find anything sideways, it should be a vertical ship
    if (!isHorizontal) {
      // Look UP
      for (char row = shipRow - 1; row >= 'A'; row--) {
        GridPosition upPos(row, shipCol);
        std::map<GridPosition, Shot::Impact>::iterator shotFindIt =
            shots.find(upPos);

        if (shotFindIt != shots.end() && (shotFindIt->second == Shot::HIT ||
                                          shotFindIt->second == Shot::SUNKEN)) {
          shipPositions.insert(upPos);
        } else {
          break;
        }
      }

      // Look DOWN
      char maxRow = 'A' + rows - 1;
      for (char row = shipRow + 1; row <= maxRow; row++) {
        GridPosition downPos(row, shipCol);
        std::map<GridPosition, Shot::Impact>::iterator shotFindIt =
            shots.find(downPos); // here we are searching for the ship

        if (shotFindIt != shots.end() && (shotFindIt->second == Shot::HIT ||
                                          shotFindIt->second == Shot::SUNKEN)) {
          shipPositions.insert(
              downPos); // here we are inserting the ships positions
        } else {
          break;
        }
      }
    }

    // Now that we've found all the coordinates, we can 'reconstruct' the ship.
    // The set is sorted, so the first and last items are the bow and stern!
    if (!shipPositions.empty()) {
      GridPosition bow = *shipPositions.begin();
      GridPosition stern = *shipPositions.rbegin();

      Ship sunkenShip(bow, stern);
      sunkenShips.push_back(sunkenShip);
    }
  }
}

const std::map<GridPosition, Shot::Impact> &OpponentGrid::getShotsAt() const {
  return shots;
} // here we are returning the shots

const std::vector<Ship> &OpponentGrid::getSunkenShips() const {
  return sunkenShips;
} // here we are returning the sunken ships
