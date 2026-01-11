/**
 * @file fullgametest.cpp
 * @brief A comprehensive test that simulates a real gameplay session.
 *
 * It goes through ship placement, invalid moves, taking shots,
 * and eventually sinking the entire fleet to ensure every part of
 * the code works together perfectly.
 */

#include "Board.h"
#include "ConsoleView.h"
#include <iostream>
#include <memory>
#include <string>

using namespace std;

// Tracking test success rates
int testsPassed = 0;
int testsFailed = 0;

/**
 * A bit more advanced assertion helper that counts passes and failures.
 */
void assertTest(bool condition, const string &testName) {
  if (condition) {
    testsPassed++;
    cout << "  [PASS] " << testName << endl;
  } else {
    testsFailed++;
    cout << "  [FAIL] " << testName << endl;
  }
}

/**
 * Simple utility to draw headers in the test output.
 */
void printSeparator(const string &title) {
  cout << endl;
  cout << "============================================" << endl;
  cout << title << endl;
  cout << "============================================" << endl;
}

/**
 * The 'Grand Tour' of our Battleship implementation.
 */
void fullGameTest() {
  printSeparator("FULL GAME TEST - BATTLESHIP");

  // --- PHASE 1: Ship Placement ---
  printSeparator("PHASE 1: Ship Placement");

  std::unique_ptr<Board> board(new Board(10, 10));
  ConsoleView view(board.get());
  OwnGrid &ownGrid = board->getOwnGrid();
  OpponentGrid &opponentGrid = board->getOpponentGrid();

  cout << "\nPlacing all 10 ships according to German Battleship rules:"
       << endl;
  cout << "  - 1x Carrier (5), 2x Battleships (4), 3x Destroyers (3), 4x "
          "Submarines (2)"
       << endl;

  // Placing a variety of ships (some horizontal, some vertical)
  assertTest(ownGrid.placeShip(Ship{GridPosition{"A1"}, GridPosition{"A5"}}),
             "Place Carrier at A1-A5");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"C1"}, GridPosition{"C4"}}),
             "Place Battleship 1 at C1-C4");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"E6"}, GridPosition{"E9"}}),
             "Place Battleship 2 at E6-E9");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"C6"}, GridPosition{"C8"}}),
             "Place Destroyer 1 at C6-C8");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"G1"}, GridPosition{"G3"}}),
             "Place Destroyer 2 at G1-G3");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"G5"}, GridPosition{"I5"}}),
             "Place Destroyer 3 at G5-I5");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"I1"}, GridPosition{"I2"}}),
             "Place Submarine 1 at I1-I2");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"G7"}, GridPosition{"G8"}}),
             "Place Submarine 2 at G7-G8");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"I7"}, GridPosition{"I8"}}),
             "Place Submarine 3 at I7-I8");
  assertTest(ownGrid.placeShip(Ship{GridPosition{"I10"}, GridPosition{"J10"}}),
             "Place Submarine 4 at I10-J10");

  assertTest(ownGrid.getShips().size() == 10,
             "Confirming all 10 ships are on the board");

  cout << "\nVisualizing the starting board:" << endl;
  view.print();

  // --- PHASE 2: Rule Violations ---
  printSeparator("PHASE 2: Illegal Moves Protection");

  assertTest(!ownGrid.placeShip(Ship{GridPosition{"J3"}, GridPosition{"J4"}}),
             "Block 11th ship (limit is 10)");

  std::unique_ptr<Board> board2(new Board(10, 10));
  board2->getOwnGrid().placeShip(Ship{GridPosition{"E5"}, GridPosition{"E7"}});
  assertTest(!board2->getOwnGrid().placeShip(
                 Ship{GridPosition{"D5"}, GridPosition{"D7"}}),
             "Block ships that touch");

  assertTest(!Ship{GridPosition{"A1"}, GridPosition{"C3"}}.isValid(),
             "Block diagonal ships");
  assertTest(!board->getOwnGrid().placeShip(
                 Ship{GridPosition{"J9"}, GridPosition{"J12"}}),
             "Block off-grid placement");

  // --- PHASE 3: Incoming Attacks ---
  printSeparator("PHASE 3: Receiving Fire");

  assertTest(ownGrid.takeBlow(Shot{GridPosition{"B1"}}) == Shot::NONE,
             "Shot at empty B1 is a MISS");
  assertTest(ownGrid.takeBlow(Shot{GridPosition{"A1"}}) == Shot::HIT,
             "Shot at A1 is a HIT on the Carrier");
  ownGrid.takeBlow(Shot{GridPosition{"A2"}});
  ownGrid.takeBlow(Shot{GridPosition{"A3"}});
  ownGrid.takeBlow(Shot{GridPosition{"A4"}});
  assertTest(ownGrid.takeBlow(Shot{GridPosition{"A5"}}) == Shot::SUNKEN,
             "Final shot at A5 SUNK the Carrier");

  cout << "\nBoard state after the Carrier is destroyed:" << endl;
  view.print();

  // --- PHASE 4: Attacking the Enemy ---
  printSeparator("PHASE 4: Tracking Our Attacks");

  opponentGrid.shotResult(Shot{GridPosition{"A1"}}, Shot::NONE); // Miss
  opponentGrid.shotResult(Shot{GridPosition{"C2"}}, Shot::HIT);  // Hit!
  opponentGrid.shotResult(Shot{GridPosition{"C3"}}, Shot::HIT);
  opponentGrid.shotResult(Shot{GridPosition{"C4"}}, Shot::HIT);
  opponentGrid.shotResult(Shot{GridPosition{"C5"}},
                          Shot::SUNKEN); // Found a size 4 ship

  assertTest(opponentGrid.getSunkenShips().size() == 1,
             "Tracker correctly identified 1 sunken ship");
  assertTest(opponentGrid.getSunkenShips()[0].length() == 4,
             "Tracker correctly identified ship size (4)");

  // --- PHASE 5: Coordinate Edge Cases ---
  printSeparator("PHASE 5: Geometry & Edge Cases");

  assertTest(GridPosition{"J10"}.isValid(), "J10 is a valid coordinate");
  assertTest((string)GridPosition{"A1"} == "A1", "String conversion check");
  assertTest(GridPosition{"A1"} < GridPosition{"A2"}, "sorting order (col)");
  assertTest(GridPosition{"A1"} < GridPosition{"B1"}, "sorting order (row)");

  // --- PHASE 6: Victory Simulation ---
  printSeparator("PHASE 6: Sinking the Entire Fleet");

  cout << "\nSimulating final strikes to clear the board..." << endl;

  // Sinking everything else...
  ownGrid.takeBlow(Shot{GridPosition{"C2"}});
  ownGrid.takeBlow(Shot{GridPosition{"C1"}});
  ownGrid.takeBlow(Shot{GridPosition{"C3"}});
  assertTest(ownGrid.takeBlow(Shot{GridPosition{"C4"}}) == Shot::SUNKEN,
             "Battleship 1 sunk");

  // (Remaining ships are sunk in the background here for brevity in logs...)
  for (int i = 6; i <= 9; i++)
    ownGrid.takeBlow(Shot{GridPosition('E', i)});
  for (int i = 6; i <= 8; i++)
    ownGrid.takeBlow(Shot{GridPosition('C', i)});
  for (int i = 1; i <= 3; i++)
    ownGrid.takeBlow(Shot{GridPosition('G', i)});
  for (char r = 'G'; r <= 'I'; r++)
    ownGrid.takeBlow(Shot{GridPosition(r, 5)});
  ownGrid.takeBlow(Shot{GridPosition{"G7"}});
  ownGrid.takeBlow(Shot{GridPosition{"G8"}});
  ownGrid.takeBlow(Shot{GridPosition{"I7"}});
  ownGrid.takeBlow(Shot{GridPosition{"I8"}});
  ownGrid.takeBlow(Shot{GridPosition{"I1"}});
  ownGrid.takeBlow(Shot{GridPosition{"I2"}});
  ownGrid.takeBlow(Shot{GridPosition{"I10"}});
  ownGrid.takeBlow(Shot{GridPosition{"J10"}});

  cout << "\nFinal board state with 0 active ships:" << endl;
  view.print();

  printSeparator("TEST SUMMARY");
  cout << "  Passed: " << testsPassed << " | Failed: " << testsFailed << endl;
  if (testsFailed == 0)
    cout << "\n*** ALL SYSTEMS NOMINAL - READY FOR DEPLOYMENT ***" << endl;
}

void runFullGameTest() { fullGameTest(); }
