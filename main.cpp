/**
 * @file main.cpp
 * @brief Entry point for the Battleship game tests.
 *
 * This file coordinates the execution of all our test suites,
 * from basic coordinate checks to a full game simulation.
 */

#include <iostream>

// These functions come from our various test files
void part1tests();      // Basic GridPosition and Ship tests
void part2tests();      // Ship placement and arrangement rules
void part3tests();      // Shot mechanics and sinking ships
void runFullGameTest(); // A complete simulation of a gameplay session

/**
 * Executes each part of the project tests in order.
 */
int main() {
  std::cout << "=== Running Part 1 Tests (Basic Classes) ===" << std::endl;
  part1tests();
  std::cout << "Part 1 tests completed." << std::endl;
  std::cout << std::endl;

  std::cout << "=== Running Part 2 Tests (Grid Rules) ===" << std::endl;
  part2tests();
  std::cout << "Part 2 tests completed." << std::endl;
  std::cout << std::endl;

  std::cout << "=== Running Part 3 Tests (Shots & Sinking) ===" << std::endl;
  part3tests();
  std::cout << "Part 3 tests completed." << std::endl;
  std::cout << std::endl;

  std::cout << "=== Running Full Game Test (Complete Simulation) ==="
            << std::endl;
  runFullGameTest();

  return 0;
}
