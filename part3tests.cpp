/*
 * part3tests.cpp
 *
 * Tests for shot mechanics (Exercise 2.3)
 */

#include <iostream>
#include <memory>

using namespace std;

#include "Board.h"

/**
 * Outputs the failedMessage on the console if condition is false.
 */
void assertTrue3(bool condition, string failedMessage) {
  if (!condition) {
    cout << failedMessage << endl;
  }
}

/**
 * Tests for shot mechanics
 */
void part3tests() {
  // Setup a board with a ship
  auto board = std::make_unique<Board>(10, 10);
  OwnGrid &ownGrid = board->getOwnGrid();

  // Place a ship at B2-B4 (length 3)
  Ship ship1(GridPosition{"B2"}, GridPosition{"B4"});
  ownGrid.placeShip(ship1);

  // Test miss
  Shot missShot(GridPosition{"A1"});
  Shot::Impact missResult = ownGrid.takeBlow(missShot);
  assertTrue3(missResult == Shot::NONE,
              "Shot at empty position should return NONE");

  // Test hit (not sinking)
  Shot hitShot1(GridPosition{"B2"});
  Shot::Impact hitResult1 = ownGrid.takeBlow(hitShot1);
  assertTrue3(hitResult1 == Shot::HIT, "First shot at ship should return HIT");

  Shot hitShot2(GridPosition{"B3"});
  Shot::Impact hitResult2 = ownGrid.takeBlow(hitShot2);
  assertTrue3(hitResult2 == Shot::HIT, "Second shot at ship should return HIT");

  // Test sinking
  Shot finalShot(GridPosition{"B4"});
  Shot::Impact sinkResult = ownGrid.takeBlow(finalShot);
  assertTrue3(sinkResult == Shot::SUNKEN,
              "Final shot at ship should return SUNKEN");

  // Test opponent grid shot tracking
  auto board2 = std::make_unique<Board>(10, 10);
  OpponentGrid &opponentGrid = board2->getOpponentGrid();

  // Record some shots
  opponentGrid.shotResult(Shot{GridPosition{"C2"}}, Shot::NONE);   // Miss
  opponentGrid.shotResult(Shot{GridPosition{"C3"}}, Shot::HIT);    // Hit
  opponentGrid.shotResult(Shot{GridPosition{"C4"}}, Shot::HIT);    // Hit
  opponentGrid.shotResult(Shot{GridPosition{"C5"}}, Shot::SUNKEN); // Sunk

  // Verify shots are recorded
  const map<GridPosition, Shot::Impact> &shots = opponentGrid.getShotsAt();
  assertTrue3(shots.count(GridPosition{"C2"}) > 0,
              "Miss shot should be recorded");
  assertTrue3(shots.at(GridPosition{"C2"}) == Shot::NONE,
              "Miss shot should have NONE impact");

  // Verify sunken ship is detected
  const vector<Ship> &sunken = opponentGrid.getSunkenShips();
  assertTrue3(sunken.size() == 1, "Should have detected 1 sunken ship");

  if (sunken.size() > 0) {
    assertTrue3(sunken[0].length() == 3, "Sunken ship should have length 3");
  }
}
