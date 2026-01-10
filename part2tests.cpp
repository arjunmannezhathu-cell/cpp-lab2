/*
 * part2tests.cpp
 *
 * Tests for ship arrangement rules (Exercise 2.2)
 */

#include <iostream>

using namespace std;

#include "Board.h"

/**
 * Outputs the failedMessage on the console if condition is false.
 */
void assertTrue2(bool condition, string failedMessage) {
  if (!condition) {
    cout << failedMessage << endl;
  }
}

/**
 * Tests for ship placement rules
 */
void part2tests() {
  // Test basic ship placement
  Board board(10, 10);
  OwnGrid &grid = board.getOwnGrid();

  // Valid ship placement
  Ship ship1(GridPosition{"B2"}, GridPosition{"B4"}); // Length 3 - Destroyer
  assertTrue2(grid.placeShip(ship1), "Should be able to place first ship");

  // Test ships cannot touch each other
  Ship touchingShip(GridPosition{"C2"},
                    GridPosition{"C4"}); // Would touch ship1
  assertTrue2(!grid.placeShip(touchingShip),
              "Should not be able to place ship touching another ship");

  // Test ships can be placed with proper gap
  Ship ship2(GridPosition{"D4"},
             GridPosition{"G4"}); // Length 4 - placed with gap
  assertTrue2(grid.placeShip(ship2),
              "Should be able to place ship with proper gap");

  // Test ship count limits
  Board board2(10, 10);
  OwnGrid &grid2 = board2.getOwnGrid();

  // Can place 4 submarines (length 2)
  assertTrue2(grid2.placeShip(Ship{GridPosition{"A1"}, GridPosition{"A2"}}),
              "Should place submarine 1");
  assertTrue2(grid2.placeShip(Ship{GridPosition{"A4"}, GridPosition{"A5"}}),
              "Should place submarine 2");
  assertTrue2(grid2.placeShip(Ship{GridPosition{"A7"}, GridPosition{"A8"}}),
              "Should place submarine 3");
  assertTrue2(grid2.placeShip(Ship{GridPosition{"C1"}, GridPosition{"C2"}}),
              "Should place submarine 4");

  // Cannot place 5th submarine
  assertTrue2(!grid2.placeShip(Ship{GridPosition{"C4"}, GridPosition{"C5"}}),
              "Should not be able to place 5th submarine");

  // Test ship must be within grid bounds
  Board board3(10, 10);
  OwnGrid &grid3 = board3.getOwnGrid();

  Ship outOfBounds(GridPosition{"J9"},
                   GridPosition{"J12"}); // Column 11-12 out of bounds
  assertTrue2(!grid3.placeShip(outOfBounds),
              "Should not be able to place ship out of bounds");

  // Test blocked area calculation
  Ship testShip(GridPosition{"E5"}, GridPosition{"E7"});
  set<GridPosition> blocked = testShip.blockedArea();

  // Should include surrounding positions
  assertTrue2(blocked.count(GridPosition{"D4"}) > 0,
              "Blocked area should include diagonal D4");
  assertTrue2(blocked.count(GridPosition{"F8"}) > 0,
              "Blocked area should include diagonal F8");
  assertTrue2(blocked.count(GridPosition{"D5"}) > 0,
              "Blocked area should include adjacent D5");
  assertTrue2(blocked.count(GridPosition{"F6"}) > 0,
              "Blocked area should include adjacent F6");
}
