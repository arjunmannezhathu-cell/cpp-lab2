#include "demo.h"
#include "Board.h"
#include "ConsoleView.h"
#include <iostream>
#include <memory>

using namespace std;

void runDemo() {
  // 1. Setup
  std::unique_ptr<Board> board(new Board(10, 10));
  ConsoleView view(board.get());

  // 2. Scenario: Placement
  cout << "--- DEMO 1: Placing a Destroyer (B2-B4) ---" << endl;
  board->getOwnGrid().placeShip(Ship(GridPosition("B2"), GridPosition("B4")));
  view.print();

  // 3. Scenario: Rule Enforcement
  cout << "\n--- DEMO 2: Rule Check (Trying to touch B2-B4 at C2-C4) ---"
       << endl;
  bool result = board->getOwnGrid().placeShip(
      Ship(GridPosition("C2"), GridPosition("C4")));
  cout << "Placement Result: "
       << (result ? "Error (Allowed)" : "Success (Rejected)") << endl;

  // 4. Scenario: Combat
  cout << "\n--- DEMO 3: Sinking the ship (Firing B2, B3, B4) ---" << endl;
  board->getOwnGrid().takeBlow(Shot(GridPosition("B2")));
  board->getOwnGrid().takeBlow(Shot(GridPosition("B3")));
  board->getOwnGrid().takeBlow(Shot(GridPosition("B4")));
  view.print();

  // 5. Scenario: Radar
  cout << "\n--- DEMO 4: Opponent Radar (Deducing ship at G5-G6) ---" << endl;
  board->getOpponentGrid().shotResult(Shot(GridPosition("G5")), Shot::HIT);
  board->getOpponentGrid().shotResult(Shot(GridPosition("G6")), Shot::SUNKEN);
  view.print();
}
