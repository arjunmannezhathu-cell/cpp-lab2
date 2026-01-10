# GridPosition Explanation

## What is this?
Think of this as a **GPS coordinate** for the battleship board. Just like how you find a city using latitude and longitude, this class helps the computer find a specific square on a 10x10 grid (like "B5").

## What is its job? (Duties)
1. **Store a location**: It remembers a Row (letter A-J) and a Column (number 1-10).
2. **Read strings**: It can take a piece of text like "C7" and figure out it means "Row C, Column 7".
3. **Verify validity**: it checks if a coordinate actually exists (e.g., "Z99" is invalid because our board is too small).
4. **Compare positions**: It can tell if two squares are the same or which one comes first (useful for sorting).

## Inside the Code (Variables)
- `row` (char): A single letter like 'A', 'B', or 'C'.
- `column` (int): A number like 1, 5, or 10.

## Tools it Uses (Member Functions)
- **GridPosition(char row, int column)**: A way to create a position using a letter and a number.
- **GridPosition(string position)**: A way to create a position by typing something like "A10".
- **isValid()**: A simple "Yes" or "No" check to see if the position is actually on the board.
- **getRow() / getColumn()**: These allow other parts of the program to "peak" inside and see what the letter or number is.
- **operator string()**: Converts the position back into text (like 'B2') so we can print it easily.
- **operator== and operator<**: Used to compare two positions to see if they are the same or to put them in order.

## Why do we use it?
Without this, the game wouldn't know where its ships are! It's the most basic building block of the whole project.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. The Basic Constructor
```cpp
GridPosition::GridPosition(char row, int column) {
  this->row = row;
  this->column = column;
}
```
- **What it does**: This is the simplest way to create a position.
- **`this->row = row`**: We use `this->` because the parameter name and the class variable name are both "row." Telling the computer "assign the parameter row to MY row" avoids confusion.

### 2. The String Constructor (The "Smart" One)
```cpp
GridPosition::GridPosition(std::string position) {
  if (position.length() >= 2) {
    this->row = position[0]; // Take the first character (e.g., 'B')
    
    std::string columnStr = position.substr(1); // Take everything after 'B' (e.g., "10")
    std::istringstream columnStream(columnStr); // Turn that string into a "stream"
    columnStream >> this->column; // Extract the number "10" as an integer
    
    if (columnStream.fail()) { this->column = 0; } // If it wasn't a number, it's invalid
  } else {
    this->row = '@'; // Mark as invalid if the string is too short
    this->column = 0;
  }
}
```
- **How it works**: It slices the string like a cake. It takes the first letter and then pipes the rest through a `columnStream` to turn "10" (text) into 10 (number).

### 3. Validity Check
```cpp
bool GridPosition::isValid() const {
  bool validRow = (row >= 'A') && (row <= 'Z');
  bool validColumn = (column > 0);
  return validRow && validColumn;
}
```
- **The Logic**: It simply checks if the row letter is between A and Z and the column is a positive number. If both are true, the position is "legal."

### 4. Comparison (The Sorting Secret)
```cpp
bool GridPosition::operator<(const GridPosition &other) const {
  if (this->row != other.row) {
    return this->row < other.row; // Sort by Row first (A < B)
  }
  return this->column < other.column; // If Rows are equal, sort by Column (1 < 2)
}
```
- **Why this matters**: This allows the computer to put positions in a list from top-left to bottom-right. It's essential for keeping the data organized!
