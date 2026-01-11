/**
 * @file part3tests.cpp
 * @brief Tests for shooting mechanics (Exercise 2.3).
 *
 * Verifies that the game correctly identifies misses, hits, and sinking ships,
 * and that the opponent tracker works.
 */

#include "Board.h"
#include <iostream>
#include <memory>

using namespace std;

/**
 * Assertion helper to keep the output clean.
 */
void assertTrue3(bool condition, string failedMessage) {
  if (!condition) {
    cout << "  [FAIL] " << failedMessage << endl;
  }
}

/**
 * Tests for the 'takeBlow' and 'shotResult' logic.
 */
void part3tests() {
  // --- OwnGrid Shot Tests ---
  std::unique_ptr<Board> board(new Board(10, 10));
  OwnGrid &ownGrid = board->getOwnGrid();

  // Place a target ship
  Ship ship1(GridPosition{"B2"}, GridPosition{"B4"}); // Length 3
  ownGrid.placeShip(ship1);

  // 1. Test a clear miss
  Shot missShot(GridPosition{"A1"});
  assertTrue3(ownGrid.takeBlow(missShot) == Shot::NONE,
              "Shot at A1 should be a MISS");

  // 2. Test hits that don't sink the ship yet
  assertTrue3(ownGrid.takeBlow(Shot{GridPosition{"B2"}}) == Shot::HIT,
              "B2 should be a HIT");
  assertTrue3(ownGrid.takeBlow(Shot{GridPosition{"B3"}}) == Shot::HIT,
              "B3 should be a HIT");

  // 3. Test the final shot that sinks it
  assertTrue3(ownGrid.takeBlow(Shot{GridPosition{"B4"}}) == Shot::SUNKEN,
              "B4 should be SUNKEN");

  // --- OpponentGrid Tracker Tests ---
  std::unique_ptr<Board> board2(new Board(10, 10));
  OpponentGrid &opponentGrid = board2->getOpponentGrid();

  // Record a sequence of shots that should reveal a horizontal ship
  opponentGrid.shotResult(Shot{GridPosition{"C2"}}, Shot::NONE); // Miss
  opponentGrid.shotResult(Shot{GridPosition{"C3"}}, Shot::HIT);  // Part of ship
  opponentGrid.shotResult(Shot{GridPosition{"C4"}}, Shot::HIT);  // Part of ship
  opponentGrid.shotResult(Shot{GridPosition{"C5"}},
                          Shot::SUNKEN); // Whole ship found!

  // The grid should have automatically deduced the ship's full location (C3-C5)
  const vector<Ship> &sunken = opponentGrid.getSunkenShips();
  assertTrue3(sunken.size() == 1, "Should have detected exactly 1 sunken ship");

  if (!sunken.empty()) {
    assertTrue3(sunken[0].length() == 3, "Deducted ship should have length 3");
  }
}
