/**
 * @file GridPosition.cpp
 * @brief Implementation of the GridPosition class.
 *
 * This file handles how we represent and validate coordinates on our
 * battleship board (like 'B5' or 'J10').
 */

#include "GridPosition.h"
#include <sstream>

/**
 * Default Constructor.
 * Sets values to 0 initially.
 */
GridPosition::GridPosition() {
  this->row = 0;
  this->column = 0;
}

/**
 * constructor that just sets the row letter and column number directly.
 */
GridPosition::GridPosition(char row, int column) {
  this->row = row;
  this->column = column;
}

/**
 * constructor that takes a string like "A10" and pulls it apart.
 *
 */
GridPosition::GridPosition(std::string position) {
  // We need at least two characters (like 'A1') to  try parsing
  if (position.length() >= 2) {
    this->row = position[0]; // The first character is always our row (A-J)

    // We use a stream to turn the remaining text (like "10") into a real
    // integer
    std::string columnStr = position.substr(1);
    std::istringstream columnStream(columnStr);
    columnStream >> this->column;

    // If the person typed something that wasn't a number, we mark the column as
    // 0
    if (columnStream.fail()) {
      this->column = 0;
    }
  } else {
    // String was too short or invalid, so we set invalid 'safety' values
    this->row = '@';
    this->column = 0;
  }
}

/**
 * Checks if the position actually fits on a standard board.
 * Rows must be between A and Z, and columns must be 1 or higher.
 */
bool GridPosition::isValid() const {
  bool validRow = (row >= 'A') && (row <= 'Z');
  bool validColumn = (column > 0);

  return validRow && validColumn;
}

char GridPosition::getRow() const { return row; }

int GridPosition::getColumn() const { return column; }

/**
 * Lets us easily turn a position back into a string like "B2" for printing.
 */
GridPosition::operator std::string() const {
  std::ostringstream positionStream;
  positionStream << row << column;
  return positionStream.str();
}

/**
 * Checks if two positions are pointing to the exact same square.
 */
bool GridPosition::operator==(const GridPosition &other) const {
  return (this->row == other.row) && (this->column == other.column);
}

/**
 * This is used for sorting positions in sets or maps.
 * We prioritize rows first (A comes before B), then columns (1 comes before 2).
 */
bool GridPosition::operator<(const GridPosition &other) const {
  if (this->row != other.row) {
    return this->row < other.row;
  }
  return this->column < other.column;
}
