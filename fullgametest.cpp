/*
 * fullgametest.cpp
 *
 * Comprehensive test that plays an entire game of Battleship
 * to verify all functionality works correctly.
 */

#include "Board.h"
#include "ConsoleView.h"
#include <iostream>
#include <string>

using namespace std;

// Test assertion helper
int testsPassed = 0;
int testsFailed = 0;

void assertTest(bool condition, const string &testName) {
  if (condition) {
    testsPassed++;
    cout << "  [PASS] " << testName << endl;
  } else {
    testsFailed++;
    cout << "  [FAIL] " << testName << endl;
  }
}

void printSeparator(const string &title) {
  cout << endl;
  cout << "============================================" << endl;
  cout << title << endl;
  cout << "============================================" << endl;
}

void fullGameTest() {
  printSeparator("FULL GAME TEST - BATTLESHIP");

  // =========================================
  // PHASE 1: SETUP - PLACE ALL 10 SHIPS
  // =========================================
  printSeparator("PHASE 1: Ship Placement");

  Board board(10, 10);
  ConsoleView view(&board);
  OwnGrid &ownGrid = board.getOwnGrid();
  OpponentGrid &opponentGrid = board.getOpponentGrid();

  cout << "\nPlacing all 10 ships according to German Battleship rules:"
       << endl;
  cout << "  - 1x Carrier (length 5)" << endl;
  cout << "  - 2x Battleship (length 4)" << endl;
  cout << "  - 3x Destroyer (length 3)" << endl;
  cout << "  - 4x Submarine (length 2)" << endl;
  cout << endl;

  // Place Carrier (length 5)
  Ship carrier(GridPosition{"A1"}, GridPosition{"A5"});
  assertTest(carrier.isValid(), "Carrier is valid");
  assertTest(carrier.length() == 5, "Carrier length is 5");
  assertTest(ownGrid.placeShip(carrier), "Place Carrier at A1-A5");

  // Place Battleships (length 4)
  Ship battleship1(GridPosition{"C1"}, GridPosition{"C4"});
  assertTest(battleship1.isValid(), "Battleship 1 is valid");
  assertTest(battleship1.length() == 4, "Battleship 1 length is 4");
  assertTest(ownGrid.placeShip(battleship1), "Place Battleship 1 at C1-C4");

  Ship battleship2(GridPosition{"E6"}, GridPosition{"E9"});
  assertTest(battleship2.isValid(), "Battleship 2 is valid");
  assertTest(ownGrid.placeShip(battleship2), "Place Battleship 2 at E6-E9");

  // Place Destroyers (length 3)
  Ship destroyer1(GridPosition{"C6"}, GridPosition{"C8"});
  assertTest(destroyer1.isValid(), "Destroyer 1 is valid");
  assertTest(destroyer1.length() == 3, "Destroyer 1 length is 3");
  assertTest(ownGrid.placeShip(destroyer1), "Place Destroyer 1 at C6-C8");

  Ship destroyer2(GridPosition{"G1"}, GridPosition{"G3"});
  assertTest(ownGrid.placeShip(destroyer2), "Place Destroyer 2 at G1-G3");

  Ship destroyer3(GridPosition{"G5"}, GridPosition{"I5"});
  assertTest(ownGrid.placeShip(destroyer3), "Place Destroyer 3 at G5-I5");

  // Place Submarines (length 2)
  Ship submarine1(GridPosition{"I1"}, GridPosition{"I2"});
  assertTest(submarine1.isValid(), "Submarine 1 is valid");
  assertTest(submarine1.length() == 2, "Submarine 1 length is 2");
  assertTest(ownGrid.placeShip(submarine1), "Place Submarine 1 at I1-I2");

  Ship submarine2(GridPosition{"G7"}, GridPosition{"G8"});
  assertTest(ownGrid.placeShip(submarine2), "Place Submarine 2 at G7-G8");

  Ship submarine3(GridPosition{"I7"}, GridPosition{"I8"});
  assertTest(ownGrid.placeShip(submarine3), "Place Submarine 3 at I7-I8");

  Ship submarine4(GridPosition{"J10"}, GridPosition{"I10"});
  assertTest(ownGrid.placeShip(submarine4), "Place Submarine 4 at I10-J10");

  // Verify we have 10 ships
  assertTest(ownGrid.getShips().size() == 10, "Total ships placed: 10");

  cout << "\nBoard after placing all ships:" << endl;
  view.print();

  // =========================================
  // PHASE 2: TEST INVALID PLACEMENTS
  // =========================================
  printSeparator("PHASE 2: Invalid Placement Tests");

  // Try to place 11th ship (exceeds limit)
  Ship extraSubmarine(GridPosition{"J3"}, GridPosition{"J4"});
  assertTest(!ownGrid.placeShip(extraSubmarine),
             "Cannot place extra submarine (limit reached)");

  // Try to place ship that touches another
  Board board2(10, 10);
  board2.getOwnGrid().placeShip(Ship{GridPosition{"E5"}, GridPosition{"E7"}});
  assertTest(!board2.getOwnGrid().placeShip(
                 Ship{GridPosition{"D5"}, GridPosition{"D7"}}),
             "Cannot place ship touching another (adjacent row)");
  assertTest(!board2.getOwnGrid().placeShip(
                 Ship{GridPosition{"F4"}, GridPosition{"F6"}}),
             "Cannot place ship touching another (diagonal)");

  // Try to place diagonal ship
  Ship diagonalShip(GridPosition{"A1"}, GridPosition{"C3"});
  assertTest(!diagonalShip.isValid(), "Diagonal ship is invalid");

  // Try to place ship of length 1
  Ship tooShort(GridPosition{"A1"}, GridPosition{"A1"});
  assertTest(!tooShort.isValid(), "Ship of length 1 is invalid");

  // Try to place ship of length 6
  Ship tooLong(GridPosition{"A1"}, GridPosition{"A6"});
  assertTest(!tooLong.isValid(), "Ship of length 6 is invalid");

  // Try to place ship out of bounds
  Board board3(10, 10);
  Ship outOfBounds(GridPosition{"J9"}, GridPosition{"J12"});
  assertTest(!board3.getOwnGrid().placeShip(outOfBounds),
             "Cannot place ship out of bounds");

  // =========================================
  // PHASE 3: INCOMING SHOTS (takeBlow)
  // =========================================
  printSeparator("PHASE 3: Incoming Shots on Own Grid");

  // Miss shots
  Shot::Impact result;

  result = ownGrid.takeBlow(Shot{GridPosition{"B1"}});
  assertTest(result == Shot::NONE, "Shot at B1 misses (NONE)");

  result = ownGrid.takeBlow(Shot{GridPosition{"D5"}});
  assertTest(result == Shot::NONE, "Shot at D5 misses (NONE)");

  result = ownGrid.takeBlow(Shot{GridPosition{"J1"}});
  assertTest(result == Shot::NONE, "Shot at J1 misses (NONE)");

  // Hit carrier but don't sink it
  result = ownGrid.takeBlow(Shot{GridPosition{"A1"}});
  assertTest(result == Shot::HIT, "Shot at A1 hits Carrier (HIT)");

  result = ownGrid.takeBlow(Shot{GridPosition{"A2"}});
  assertTest(result == Shot::HIT, "Shot at A2 hits Carrier (HIT)");

  result = ownGrid.takeBlow(Shot{GridPosition{"A3"}});
  assertTest(result == Shot::HIT, "Shot at A3 hits Carrier (HIT)");

  result = ownGrid.takeBlow(Shot{GridPosition{"A4"}});
  assertTest(result == Shot::HIT, "Shot at A4 hits Carrier (HIT)");

  // Sink the carrier
  result = ownGrid.takeBlow(Shot{GridPosition{"A5"}});
  assertTest(result == Shot::SUNKEN, "Shot at A5 sinks Carrier (SUNKEN)");

  cout << "\nBoard after carrier sunk:" << endl;
  view.print();

  // Sink a submarine (length 2)
  result = ownGrid.takeBlow(Shot{GridPosition{"I1"}});
  assertTest(result == Shot::HIT, "Shot at I1 hits Submarine 1 (HIT)");

  result = ownGrid.takeBlow(Shot{GridPosition{"I2"}});
  assertTest(result == Shot::SUNKEN, "Shot at I2 sinks Submarine 1 (SUNKEN)");

  // Partial hits on battleship
  result = ownGrid.takeBlow(Shot{GridPosition{"C1"}});
  assertTest(result == Shot::HIT, "Shot at C1 hits Battleship 1 (HIT)");

  result = ownGrid.takeBlow(Shot{GridPosition{"C3"}});
  assertTest(result == Shot::HIT, "Shot at C3 hits Battleship 1 (HIT)");

  cout << "\nBoard after submarine sunk and battleship hit:" << endl;
  view.print();

  // =========================================
  // PHASE 4: OUTGOING SHOTS (shotResult)
  // =========================================
  printSeparator("PHASE 4: Outgoing Shots at Opponent");

  cout << "\nSimulating shots at opponent's grid:" << endl;

  // Some misses
  opponentGrid.shotResult(Shot{GridPosition{"A1"}}, Shot::NONE);
  opponentGrid.shotResult(Shot{GridPosition{"A3"}}, Shot::NONE);
  opponentGrid.shotResult(Shot{GridPosition{"B5"}}, Shot::NONE);

  assertTest(opponentGrid.getShotsAt().size() == 3, "3 shots recorded");
  assertTest(opponentGrid.getShotsAt().at(GridPosition{"A1"}) == Shot::NONE,
             "A1 recorded as miss");

  // Hit a ship without sinking
  opponentGrid.shotResult(Shot{GridPosition{"C2"}}, Shot::HIT);
  opponentGrid.shotResult(Shot{GridPosition{"C3"}}, Shot::HIT);

  assertTest(opponentGrid.getSunkenShips().size() == 0, "No ships sunk yet");

  // Sink a horizontal ship
  opponentGrid.shotResult(Shot{GridPosition{"C4"}}, Shot::HIT);
  opponentGrid.shotResult(Shot{GridPosition{"C5"}}, Shot::SUNKEN);

  assertTest(opponentGrid.getSunkenShips().size() == 1,
             "1 ship sunk on opponent grid");

  if (opponentGrid.getSunkenShips().size() > 0) {
    Ship sunken = opponentGrid.getSunkenShips()[0];
    assertTest(sunken.length() == 4, "Sunken ship has length 4");
    assertTest(sunken.occupiedArea().count(GridPosition{"C2"}) > 0,
               "Sunken ship includes C2");
    assertTest(sunken.occupiedArea().count(GridPosition{"C5"}) > 0,
               "Sunken ship includes C5");
  }

  // More misses
  opponentGrid.shotResult(Shot{GridPosition{"E5"}}, Shot::NONE);
  opponentGrid.shotResult(Shot{GridPosition{"F3"}}, Shot::NONE);

  // Sink a vertical ship
  opponentGrid.shotResult(Shot{GridPosition{"G7"}}, Shot::HIT);
  opponentGrid.shotResult(Shot{GridPosition{"H7"}}, Shot::HIT);
  opponentGrid.shotResult(Shot{GridPosition{"I7"}}, Shot::SUNKEN);

  assertTest(opponentGrid.getSunkenShips().size() == 2,
             "2 ships sunk on opponent grid");

  cout << "\nFinal board state:" << endl;
  view.print();

  // =========================================
  // PHASE 5: EDGE CASES
  // =========================================
  printSeparator("PHASE 5: Edge Cases");

  // Test GridPosition at boundaries
  GridPosition topLeft('A', 1);
  GridPosition bottomRight('J', 10);
  assertTest(topLeft.isValid(), "A1 is valid");
  assertTest(bottomRight.isValid(), "J10 is valid");

  // Test string conversion
  assertTest((string)topLeft == "A1", "A1 converts to string correctly");
  assertTest((string)bottomRight == "J10", "J10 converts to string correctly");

  // Test GridPosition from string with multi-digit column
  GridPosition multiDigit("J10");
  assertTest(multiDigit.getRow() == 'J', "J10 row is J");
  assertTest(multiDigit.getColumn() == 10, "J10 column is 10");

  // Test invalid GridPositions
  GridPosition invalidRow('@', 1);
  assertTest(!invalidRow.isValid(), "@ row is invalid");

  GridPosition invalidCol('A', 0);
  assertTest(!invalidCol.isValid(), "Column 0 is invalid");

  GridPosition negativeCol('A', -1);
  assertTest(!negativeCol.isValid(), "Negative column is invalid");

  // Test comparison operators
  assertTest(GridPosition{"A1"} < GridPosition{"A2"}, "A1 < A2");
  assertTest(GridPosition{"A1"} < GridPosition{"B1"}, "A1 < B1");
  assertTest(!(GridPosition{"B1"} < GridPosition{"A1"}), "B1 not < A1");
  assertTest(GridPosition{"A1"} == GridPosition{"A1"}, "A1 == A1");
  assertTest(!(GridPosition{"A1"} == GridPosition{"A2"}), "A1 != A2");

  // =========================================
  // PHASE 6: FULL GAME SIMULATION
  // =========================================
  printSeparator("PHASE 6: Complete Game Simulation");

  // Sink remaining ships on own grid to simulate complete game
  cout << "\nSinking all remaining ships..." << endl;

  // Finish Battleship 1 (C1-C4) - already hit C1, C3
  ownGrid.takeBlow(Shot{GridPosition{"C2"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"C4"}});
  assertTest(result == Shot::SUNKEN, "Battleship 1 sunk");

  // Sink Battleship 2 (E6-E9)
  ownGrid.takeBlow(Shot{GridPosition{"E6"}});
  ownGrid.takeBlow(Shot{GridPosition{"E7"}});
  ownGrid.takeBlow(Shot{GridPosition{"E8"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"E9"}});
  assertTest(result == Shot::SUNKEN, "Battleship 2 sunk");

  // Sink Destroyer 1 (C6-C8)
  ownGrid.takeBlow(Shot{GridPosition{"C6"}});
  ownGrid.takeBlow(Shot{GridPosition{"C7"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"C8"}});
  assertTest(result == Shot::SUNKEN, "Destroyer 1 sunk");

  // Sink Destroyer 2 (G1-G3)
  ownGrid.takeBlow(Shot{GridPosition{"G1"}});
  ownGrid.takeBlow(Shot{GridPosition{"G2"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"G3"}});
  assertTest(result == Shot::SUNKEN, "Destroyer 2 sunk");

  // Sink Destroyer 3 (G5-I5 vertical)
  ownGrid.takeBlow(Shot{GridPosition{"G5"}});
  ownGrid.takeBlow(Shot{GridPosition{"H5"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"I5"}});
  assertTest(result == Shot::SUNKEN, "Destroyer 3 sunk");

  // Sink Submarine 2 (G7-G8)
  ownGrid.takeBlow(Shot{GridPosition{"G7"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"G8"}});
  assertTest(result == Shot::SUNKEN, "Submarine 2 sunk");

  // Sink Submarine 3 (I7-I8)
  ownGrid.takeBlow(Shot{GridPosition{"I7"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"I8"}});
  assertTest(result == Shot::SUNKEN, "Submarine 3 sunk");

  // Sink Submarine 4 (I10-J10)
  ownGrid.takeBlow(Shot{GridPosition{"I10"}});
  result = ownGrid.takeBlow(Shot{GridPosition{"J10"}});
  assertTest(result == Shot::SUNKEN, "Submarine 4 sunk");

  cout << "\nFinal board - ALL SHIPS SUNK:" << endl;
  view.print();

  // =========================================
  // SUMMARY
  // =========================================
  printSeparator("TEST SUMMARY");

  cout << endl;
  cout << "Tests Passed: " << testsPassed << endl;
  cout << "Tests Failed: " << testsFailed << endl;
  cout << "Total Tests:  " << (testsPassed + testsFailed) << endl;
  cout << endl;

  if (testsFailed == 0) {
    cout << "*** ALL TESTS PASSED! ***" << endl;
  } else {
    cout << "*** SOME TESTS FAILED ***" << endl;
  }
}

// Entry point for this test
void runFullGameTest() { fullGameTest(); }
