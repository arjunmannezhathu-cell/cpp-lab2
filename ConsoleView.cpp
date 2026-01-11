/**
 * @file ConsoleView.cpp
 * @brief Implementation of the ConsoleView class.
 *
 * This file is responsible for drawing the game boards in the console.
 * It takes the Board data and turns it into readable text symbols.
 */

#include "ConsoleView.h"
#include <iostream>
#include <set>
#include <vector>

ConsoleView::ConsoleView(Board *board) { this->board = board; }

/**
 * The main render function. It builds two  grids side-by-side
 * and print them.
 */
void ConsoleView::print() {
  int rows = board->getRows();
  int columns = board->getColumns();

  // We use 2D character vectors to build the display layers first
  std::vector<std::vector<char>> ownGridDisplay(rows);
  std::vector<std::vector<char>> opponentGridDisplay(rows);

  // Layer 1: Fill everything with water ('~')
  for (int rowIdx = 0; rowIdx < rows; rowIdx++) {
    ownGridDisplay[rowIdx].resize(columns, '~');
    opponentGridDisplay[rowIdx].resize(columns, '~');
  }

  // Layer 2 (Own Grid): Draw our ships ('#')
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

  // Layer 3 (Own Grid): Overwrite with opponent's hits ('O') and misses ('^')
  const std::set<GridPosition> &ownShotAt = ownGrid.getShotAt();

  for (std::set<GridPosition>::const_iterator shotIt = ownShotAt.begin();
       shotIt != ownShotAt.end(); ++shotIt) {
    int row = shotIt->getRow() - 'A';
    int col = shotIt->getColumn() - 1;

    if (row >= 0 && row < rows && col >= 0 && col < columns) {
      if (ownGridDisplay[row][col] == '#') {
        ownGridDisplay[row][col] = 'O'; // They hit our ship!
      } else {
        ownGridDisplay[row][col] = '^'; // They hit water.
      }
    }
  }

  // Layer 2 (Opponent Grid): Draw ships we've successfully SUNK ('#')
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

  // Layer 3 (Opponent Grid): Draw our hits ('O') and misses ('^')
  const std::map<GridPosition, Shot::Impact> &opponentShots =
      opponentGrid.getShotsAt();

  for (std::map<GridPosition, Shot::Impact>::const_iterator shotIt =
           opponentShots.begin();
       shotIt != opponentShots.end(); ++shotIt) {
    int row = shotIt->first.getRow() - 'A';
    int col = shotIt->first.getColumn() - 1;

    if (row >= 0 && row < rows && col >= 0 && col < columns) {
      if (shotIt->second == Shot::NONE) {
        opponentGridDisplay[row][col] = '^'; // We missed.
      } else if (shotIt->second == Shot::HIT ||
                 shotIt->second == Shot::SUNKEN) {
        // Only mark 'O' if we haven't already marked the whole ship '#'
        if (opponentGridDisplay[row][col] != '#') {
          opponentGridDisplay[row][col] =
              'O'; // We hit but it's not sunken (yet).
        }
      }
    }
  }

  // Now, print everything to the console with column headers
  std::cout << "  ";
  for (int col = 1; col <= columns; col++) {
    std::cout << (col % 10) << " ";
  }
  std::cout << "    ";
  for (int col = 1; col <= columns; col++) {
    std::cout << (col % 10) << " ";
  }
  std::cout << std::endl;

  // Print each row, starting with the row letter (A, B, C...)
  for (int rowIdx = 0; rowIdx < rows; rowIdx++) {
    char rowLetter = 'A' + rowIdx;

    // Drawing OUR board (Left side)
    std::cout << rowLetter << " ";
    for (int colIdx = 0; colIdx < columns; colIdx++) {
      std::cout << ownGridDisplay[rowIdx][colIdx] << " ";
    }

    std::cout << "  ";

    // Drawing THE ENEMY board (Right side)
    std::cout << rowLetter << " ";
    for (int colIdx = 0; colIdx < columns; colIdx++) {
      std::cout << opponentGridDisplay[rowIdx][colIdx] << " ";
    }

    std::cout << std::endl;
  }
}
