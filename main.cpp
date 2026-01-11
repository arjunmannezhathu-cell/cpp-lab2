/*
 * main.cpp
 *
 * Battleship game demonstration
 */

#include <iostream>

// Test function declarations
void part1tests();
void part2tests();
void part3tests();
void runFullGameTest();

int main() {
  std::cout << "=== Running Part 1 Tests ===" << std::endl;
  part1tests();
  std::cout << "Part 1 tests completed." << std::endl;
  std::cout << std::endl;

  std::cout << "=== Running Part 2 Tests ===" << std::endl;
  part2tests();
  std::cout << "Part 2 tests completed." << std::endl;
  std::cout << std::endl;

  std::cout << "=== Running Part 3 Tests ===" << std::endl;
  part3tests();
  std::cout << "Part 3 tests completed." << std::endl;
  std::cout << std::endl;

  std::cout << "=== Running Full Game Test ===" << std::endl;
  runFullGameTest();

  return 0;
}
