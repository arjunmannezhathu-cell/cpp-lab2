/**
 * @file ConsoleView.cpp
 * @brief Implementation of ConsoleView class
 */

#include "ConsoleView.h"
#include <iostream>
#include <set>
#include <vector>

ConsoleView::ConsoleView(Board *board) : board(board) {}

void ConsoleView::print() {
  int rows = board->getRows();
  int columns = board->getColumns();

  // Create char arrays for both grids
  std::vector<std::vector<char>> ownGridDisplay(rows);
  std::vector<std::vector<char>> opponentGridDisplay(rows);

  // Initialize with water
  for (int rowIdx = 0; rowIdx < rows; rowIdx++) {
    ownGridDisplay[rowIdx].resize(columns, '~');
    opponentGridDisplay[rowIdx].resize(columns, '~');
  }

  // Mark ships on own grid
  OwnGrid &ownGrid = board->getOwnGrid();
  std::vector<Ship> ships = ownGrid.getShips();

  for (std::vector<Ship>::const_iterator shipIt = ships.begin();
       shipIt != ships.end(); ++shipIt) {
    std::set<GridPosition> occupied = shipIt->occupiedArea();

    for (std::set<GridPosition>::const_iterator posIt = occupied.begin();
         posIt != occupied.end(); ++posIt) {
      int row = posIt->getRow() - 'A';
      int col = posIt->getColumn() - 1;

      if (row >= 0 && row < rows && col >= 0 && col < columns) {
        ownGridDisplay[row][col] = '#';
      }
    }
  }

  // Mark hits and misses on own grid
  const std::set<GridPosition> &ownShotAt = ownGrid.getShotAt();

  for (std::set<GridPosition>::const_iterator shotIt = ownShotAt.begin();
       shotIt != ownShotAt.end(); ++shotIt) {
    int row = shotIt->getRow() - 'A';
    int col = shotIt->getColumn() - 1;

    if (row >= 0 && row < rows && col >= 0 && col < columns) {
      if (ownGridDisplay[row][col] == '#') {
        ownGridDisplay[row][col] = 'O'; // Hit
      } else {
        ownGridDisplay[row][col] = '^'; // Miss
      }
    }
  }

  // Mark sunken ships on opponent grid
  OpponentGrid &opponentGrid = board->getOpponentGrid();
  const std::vector<Ship> &sunkenShips = opponentGrid.getSunkenShips();

  for (std::vector<Ship>::const_iterator shipIt = sunkenShips.begin();
       shipIt != sunkenShips.end(); ++shipIt) {
    std::set<GridPosition> occupied = shipIt->occupiedArea();

    for (std::set<GridPosition>::const_iterator posIt = occupied.begin();
         posIt != occupied.end(); ++posIt) {
      int row = posIt->getRow() - 'A';
      int col = posIt->getColumn() - 1;

      if (row >= 0 && row < rows && col >= 0 && col < columns) {
        opponentGridDisplay[row][col] = '#';
      }
    }
  }

  // Mark shots on opponent grid
  const std::map<GridPosition, Shot::Impact> &opponentShots =
      opponentGrid.getShotsAt();

  for (std::map<GridPosition, Shot::Impact>::const_iterator shotIt =
           opponentShots.begin();
       shotIt != opponentShots.end(); ++shotIt) {
    int row = shotIt->first.getRow() - 'A';
    int col = shotIt->first.getColumn() - 1;

    if (row >= 0 && row < rows && col >= 0 && col < columns) {
      if (shotIt->second == Shot::NONE) {
        opponentGridDisplay[row][col] = '^'; // Miss
      } else if (shotIt->second == Shot::HIT ||
                 shotIt->second == Shot::SUNKEN) {
        if (opponentGridDisplay[row][col] != '#') {
          opponentGridDisplay[row][col] = 'O'; // Hit
        }
      }
    }
  }

  // Print column headers
  std::cout << "  ";
  for (int col = 1; col <= columns; col++) {
    std::cout << (col % 10) << " ";
  }
  std::cout << "    ";
  for (int col = 1; col <= columns; col++) {
    std::cout << (col % 10) << " ";
  }
  std::cout << std::endl;

  // Print each row
  for (int row = 0; row < rows; row++) {
    char rowLetter = 'A' + row;

    // Own grid
    std::cout << rowLetter << " ";
    for (int col = 0; col < columns; col++) {
      std::cout << ownGridDisplay[row][col] << " ";
    }

    std::cout << "  ";

    // Opponent grid
    std::cout << rowLetter << " ";
    for (int col = 0; col < columns; col++) {
      std::cout << opponentGridDisplay[row][col] << " ";
    }

    std::cout << std::endl;
  }
}
