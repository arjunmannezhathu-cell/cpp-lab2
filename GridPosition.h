/**
 * @file GridPosition.h
 * @brief Header for the GridPosition class.
 *
 * Defines a simple coordinate system (Row Letter, Column Number)
 * for our Battleship board.
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_

#include <string>

/**
 * @class GridPosition
 * @brief Represents a single square on the board.
 *
 * Each position is immutable (once created, it shouldn't change).
 * It's the most basic building block used to place ships and take shots.
 */
class GridPosition {
private:
  char row;   ///< Row letter (e.g., 'A', 'B', etc.)
  int column; ///< Column number (e.g., 1, 2, 3, etc.)

public:
  /**
   * @brief Build a position from a character and an integer.
   * @param row The row letter.
   * @param column The column number.
   */
  GridPosition(char row, int column);

  /**
   * @brief Build a position from a string like "B10".
   * @param position String representation of the coordinate.
   */
  GridPosition(std::string position);

  /**
   * @brief Is this position actually a legal spot on a board?
   * @return True if row is A-Z and column > 0.
   */
  bool isValid() const;

  /**
   * @brief Get the row letter.
   */
  char getRow() const;

  /**
   * @brief Get the column number.
   */
  int getColumn() const;

  /**
   * @brief Let the computer treat this object like a string (e.g., "A1").
   */
  operator std::string() const;

  /**
   * @brief Check if this position is the same as another.
   */
  bool operator==(const GridPosition &other) const;

  /**
   * @brief Comparison tool needed so we can put positions in a 'set' or 'map'.
   *
   * It sorts coordinates from top-to-bottom and left-to-right.
   */
  bool operator<(const GridPosition &other) const;
};

#endif /* GRIDPOSITION_H_ */
