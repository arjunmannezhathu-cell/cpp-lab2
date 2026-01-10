/**
 * @file GridPosition.cpp
 * @brief Implementation of GridPosition class
 */

#include "GridPosition.h"
#include <sstream>

GridPosition::GridPosition(char row, int column) {
  this->row = row;
  this->column = column;
}

GridPosition::GridPosition(std::string position) {
  // First char is the row letter
  if (position.length() >= 2) {
    this->row = position[0];

    // Rest of string is the column number
    std::string columnStr = position.substr(1);
    std::istringstream columnStream(columnStr);
    columnStream >> this->column;

    // If parsing failed, set invalid value
    if (columnStream.fail()) {
      this->column = 0;
    }
  } else {
    // Invalid string
    this->row = '@';
    this->column = 0;
  }
}

bool GridPosition::isValid() const {
  // Row must be A-Z, column must be positive
  bool validRow = (row >= 'A') && (row <= 'Z');
  bool validColumn = (column > 0);

  return validRow && validColumn;
}

char GridPosition::getRow() const { return row; }

int GridPosition::getColumn() const { return column; }

GridPosition::operator std::string() const {
  std::ostringstream positionStream;
  positionStream << row << column;
  return positionStream.str();
}

bool GridPosition::operator==(const GridPosition &other) const {
  return (this->row == other.row) && (this->column == other.column);
}

bool GridPosition::operator<(const GridPosition &other) const {
  // Order: top-left to bottom-right
  if (this->row != other.row) {
    return this->row < other.row;
  }
  return this->column < other.column;
}
