/**
 * @file GridPosition.h
 * @brief Represents a position on the battleship grid
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_

#include <string>

/**
 * @brief A position on the game board (like "B10")
 *
 * Immutable class - can't change after creation
 */
class GridPosition {
private:
  /// Row letter ('A' to 'Z')
  char row;

  /// Column number (starts at 1)
  int column;

public:
  /**
   * @brief Create position from row and column
   * @param row Row letter
   * @param column Column number
   */
  GridPosition(char row, int column);

  /**
   * @brief Create position from string like "B10"
   * @param position String representation
   */
  GridPosition(std::string position);

  /**
   * @brief Check if position is valid
   * @return true if 'A' <= row <= 'Z' and column > 0
   */
  bool isValid() const;

  /// @brief Get the row letter
  char getRow() const;

  /// @brief Get the column number
  int getColumn() const;

  /**
   * @brief Convert to string (e.g. "B10")
   */
  operator std::string() const;

  /**
   * @brief Check if two positions are equal
   */
  bool operator==(const GridPosition &other) const;

  /**
   * @brief Compare positions for ordering
   * Needed for std::set and std::map
   */
  bool operator<(const GridPosition &other) const;
};

#endif /* GRIDPOSITION_H_ */
