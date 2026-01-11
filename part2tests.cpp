/**
 * @file part2tests.cpp
 * @brief Tests for ship arrangement rules (Exercise 2.2).
 *
 * We test things like board boundaries, ship count limits, and the
 * "ships cannot touch" rule.
 */

#include "Board.h"
#include <iostream>
#include <memory>

using namespace std;

/**
 * Simple helper to report failed assertions.
 */
void assertTrue2(bool condition, string failedMessage) {
  if (!condition) {
    cout << "  [FAIL] " << failedMessage << endl;
  }
}

/**
 * Tests for ship placement logic.
 */
void part2tests() {
  // We use a unique_ptr for the board to practice modern C++ memory management
  std::unique_ptr<Board> board(new Board(10, 10));
  OwnGrid &grid = board->getOwnGrid();

  // 1. Placing a valid ship should work
  Ship ship1(GridPosition{"B2"}, GridPosition{"B4"});
  assertTrue2(grid.placeShip(ship1),
              "Should be able to place a Destroyer at B2-B4");

  // 2. Rule: Ships cannot touch each other (not even diagonally)
  Ship touchingShip(GridPosition{"C2"},
                    GridPosition{"C4"}); // This is right next to ship1
  assertTrue2(!grid.placeShip(touchingShip),
              "Should block ships that touch others");

  // 3. Placing with a 1-square gap should be allowed
  Ship ship2(GridPosition{"D4"}, GridPosition{"G4"});
  assertTrue2(grid.placeShip(ship2),
              "Should allow placement with a proper gap");

  // 4. Rule: You can't place more ships than allowed (inventory limits)
  std::unique_ptr<Board> board2(new Board(10, 10));
  OwnGrid &grid2 = board2->getOwnGrid();

  // Let's try placing 5 submarines (the limit is 4)
  grid2.placeShip(Ship{GridPosition{"A1"}, GridPosition{"A2"}});
  grid2.placeShip(Ship{GridPosition{"A4"}, GridPosition{"A5"}});
  grid2.placeShip(Ship{GridPosition{"A7"}, GridPosition{"A8"}});
  grid2.placeShip(Ship{GridPosition{"C1"}, GridPosition{"C2"}});
  assertTrue2(!grid2.placeShip(Ship{GridPosition{"C4"}, GridPosition{"C5"}}),
              "Should block the 5th submarine since the limit is 4");

  // 5. Rule: Ships must be completely inside the board
  std::unique_ptr<Board> board3(new Board(10, 10));
  OwnGrid &grid3 = board3->getOwnGrid();

  Ship outOfBounds(GridPosition{"J9"},
                   GridPosition{"J12"}); // Extends past column 10
  assertTrue2(!grid3.placeShip(outOfBounds),
              "Should block ships that go off-grid");

  // 6. Checking the 'blockedArea' logic (the buffer zone around a ship)
  Ship testShip(GridPosition{"E5"}, GridPosition{"E7"});
  set<GridPosition> blocked = testShip.blockedArea();

  assertTrue2(blocked.count(GridPosition{"D4"}) > 0,
              "Blocked area should include D4 (diagonal)");
  assertTrue2(blocked.count(GridPosition{"F8"}) > 0,
              "Blocked area should include F8 (diagonal)");
  assertTrue2(blocked.count(GridPosition{"D5"}) > 0,
              "Blocked area should include D5 (adjacent)");
}
