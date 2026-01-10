/**
 * @file OpponentGrid.cpp
 * @brief Implementation of OpponentGrid class
 */

#include "OpponentGrid.h"
#include <set>

OpponentGrid::OpponentGrid(int rows, int columns)
    : rows(rows), columns(columns) {}

int OpponentGrid::getRows() const { return rows; }

int OpponentGrid::getColumns() const { return columns; }

void OpponentGrid::shotResult(const Shot &shot, Shot::Impact impact) {
  GridPosition target = shot.getTargetPosition();
  shots[target] = impact;

  // If ship sunk, figure out where it was
  if (impact == Shot::SUNKEN) {
    std::set<GridPosition> shipPositions;
    shipPositions.insert(target);

    char shipRow = target.getRow();
    int shipCol = target.getColumn();

    bool isHorizontal = false;

    // Look left for more hits
    for (int col = shipCol - 1; col >= 1; col--) {
      GridPosition leftPos(shipRow, col);
      std::map<GridPosition, Shot::Impact>::iterator shotFindIt =
          shots.find(leftPos);

      if (shotFindIt != shots.end() && (shotFindIt->second == Shot::HIT ||
                                        shotFindIt->second == Shot::SUNKEN)) {
        shipPositions.insert(leftPos);
        isHorizontal = true;
      } else {
        break;
      }
    }

    // Look right
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

    // If not horizontal, check vertical
    if (!isHorizontal) {
      // Look up
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

      // Look down
      char maxRow = 'A' + rows - 1;
      for (char row = shipRow + 1; row <= maxRow; row++) {
        GridPosition downPos(row, shipCol);
        std::map<GridPosition, Shot::Impact>::iterator shotFindIt =
            shots.find(downPos);

        if (shotFindIt != shots.end() && (shotFindIt->second == Shot::HIT ||
                                          shotFindIt->second == Shot::SUNKEN)) {
          shipPositions.insert(downPos);
        } else {
          break;
        }
      }
    }

    // Create ship from first and last position
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
}

const std::vector<Ship> &OpponentGrid::getSunkenShips() const {
  return sunkenShips;
}
