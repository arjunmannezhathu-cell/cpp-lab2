# Battleship Project: Comprehensive Documentation

This document provides a complete guide to the Battleship game implementation, including high-level summaries and line-by-line code walkthroughs.

## Table of Contents
1. [GridPosition](#gridposition-explanation)
2. [Ship](#ship-explanation)
3. [Shot](#shot-explanation)
4. [OwnGrid](#owngrid-explanation)
5. [OpponentGrid](#opponentgrid-explanation)
6. [Board](#board-explanation)
7. [ConsoleView](#consoleview-explanation)
8. [main.cpp](#main-explanation)
9. [Part 1 Tests](#part1tests-explanation)
10. [Part 2 Tests](#part2tests-explanation)
11. [Part 3 Tests](#part3tests-explanation)
12. [Full Game Simulation](#fullgametest-explanation)

---

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

---

# Ship Explanation

## What is this?
A **Ship** is an object that occupies several squares on the board. Imagine it like a row of LEGO bricks—it has a start (the bow) and an end (the stern).

## What is its job? (Duties)
1. **Define a ship**: It holds the two end-points of a ship.
2. **Check for "Straightness"**: It makes sure the ship is either perfectly horizontal or perfectly vertical. Diagonal ships are not allowed!
3. **Calculate Length**: It figures out how many squares long the ship is (e.g., A1 to A3 is 3 squares).
4. **Identify Occupied Space**: It creates a list of every single square the ship covers.
5. **Identify "Blocked" Space**: This is an extra feature! It finds the ship's area PLUS all the squares immediately surrounding it. This helps us ensure two ships never touch each other.

## Inside the Code (Variables)
- `bow` (GridPosition): The "front" coordinate of the ship.
- `stern` (GridPosition): The "back" coordinate of the ship.

## Tools it Uses (Member Functions)
- **Ship(bow, stern)**: Connects two points to create a ship.
- **isValid()**: Checks three things: Are the points on the board? Is it straight? Is the length between 2 and 5?
- **getBow() / getStern()**: Let you see the end-points.
- **length()**: Returns the number of segments (e.g., 2, 3, 4, or 5).
- **occupiedArea()**: Returns a "set" (a list of unique squares) that the ship physically sits on.
- **blockedArea()**: Returns the occupied squares AND their neighbors. This is the "no-go zone" for other ships.

## Why do we use it?
It's the heart of the game! We need this to know where the targets are and to make sure players follow the rules of the sea.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. Validity Rules
```cpp
bool Ship::isValid() const {
  if (!bow.isValid() || !stern.isValid()) return false; // Both ends must exist

  bool isHorizontal = (bow.getRow() == stern.getRow());
  bool isVertical = (bow.getColumn() == stern.getColumn());

  if (!isHorizontal && !isVertical) return false; // No diagonal ships!

  int shipLength = length();
  return (shipLength >= 2 && shipLength <= 5); // Must be size 2 to 5
}
```
- **The "Straight-edge" Check**: It compares the row and column of the bow and stern. If the row is the same, it's horizontal. If the column is the same, it's vertical. Anything else is an illegal diagonal.

### 2. Calculating Length
```cpp
int Ship::length() const {
  if (bow.getRow() == stern.getRow()) {
    return std::abs(stern.getColumn() - bow.getColumn()) + 1;
  } else {
    return std::abs(stern.getRow() - bow.getRow()) + 1;
  }
}
```
- **The Math**: It subtracts one coordinate from the other and adds 1. We use `abs` (absolute value) so the answer is always positive, even if the stern coordinate is "smaller" than the bow.

### 3. Occupied Area Logic
```cpp
std::set<GridPosition> Ship::occupiedArea() const {
  std::set<GridPosition> occupied;
  // ... loop from start to end ...
  for (int col = startCol; col <= endCol; col++) {
    occupied.insert(GridPosition(bow.getRow(), col));
  }
  return occupied;
}
```
- **The Loop**: It creates a `GridPosition` for every single square between the bow and the stern and puts them into a "container" called a `set`.

### 4. The "No-Touching" Rule (Blocked Area)
```cpp
std::set<GridPosition> Ship::blockedArea() const {
  std::set<GridPosition> blocked;
  for (const auto& gridPos : occupiedArea()) {
    for (int rowOffset = -1; rowOffset <= 1; rowOffset++) {
      for (int colOffset = -1; colOffset <= 1; colOffset++) {
        blocked.insert(GridPosition(gridPos.getRow() + rowOffset, gridPos.getColumn() + colOffset));
      }
    }
  }
  return blocked;
}
```
- **The 3x3 Grid**: For every square the ship sits on, the code looks at all 8 neighbor squares (using a double loop of -1, 0, and +1 offsets). This creates a "force field" around the ship that no other ship can enter!

---

# Shot Explanation

## What is this?
The **Shot** is a single "Missile" or "Attack." It's a simple package that says "I am attacking this spot, and here is what happened."

## What is its job? (Duties)
1. **Hold a target**: It remembers which square was attacked (like "E5").
2. **Define outcomes**: It contains a list of possibilities (Impacts):
   - **NONE**: Splash! A total miss.
   - **HIT**: Clang! You hit a ship segment.
   - **SUNKEN**: BOOM! You destroyed the entire ship.

## Inside the Code (Variables)
- `targetPosition` (GridPosition): The exact square being targeted.
- `Impact` (enum): A special list that can only be NONE, HIT, or SUNKEN.

## Tools it Uses (Member Functions)
- **Shot(targetPosition)**: Prepares a new missile for a specific square.
- **getTargetPosition()**: Tells you where the missile is heading.

## Why do we use it?
It's a "data messenger." Instead of just sending a coordinate, we send a "Shot" object which is more descriptive and easier for the classes to understand.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. The Impact Enum
```cpp
enum Impact { NONE, HIT, SUNKEN };
```
- **The Concept**: This is a custom "type." Instead of using confusing numbers like 0, 1, or 2, we use human words. It's like having a multiple-choice question where the only allowed answers are NONE, HIT, or SUNKEN.

### 2. Simple Data Holding
```cpp
GridPosition Shot::getTargetPosition() const {
  return targetPosition;
}
```
- **Const Function**: This is a "Getter." It simply spits out the stored coordinate. The `const` at the end promises the computer that this function will *never* change the target by accident—it's only for reading.

---

# OwnGrid Explanation

## What is this?
Think of this as **your half of the game board**. It's the private map where you hide your ships and watch your opponent's missiles splash down (or hit!).

## What is its job? (Duties)
1. **Manage your fleet**: It keeps a list of all 10 ships you've placed.
2. **Enforce placement rules**: It makes sure you don't place too many ships, that they don't go off the edge, and that they don't touch each other.
3. **Record incoming fire**: When the opponent shoots, this class remembers where they hit.
4. **Report Damage**: It tells the game if a shot was a miss, a hit, or if it completely sank one of your ships.

## Inside the Code (Variables)
- `rows` and `columns` (int): The height and width of your board (10x10).
- `ships` (vector): A list of all your active ships.
- `availableShips` (map): A "shopping list" that keeps track of how many ships of each size (2, 3, 4, 5) you still have left to place.
- `shotAt` (set): A list of every coordinate the opponent has fired at on your board.

## Tools it Uses (Member Functions)
- **placeShip(ship)**: This is the "Traffic Cop." It checks every rule (no touching, stay in bounds, etc.). If even one rule is broken, it says "Invalid" and won't let you place it.
- **takeBlow(shot)**: This handles an incoming missile.
  - It records the shot.
  - It checks if any ship was hit.
  - If it was the *last* segment of a ship, it reports "SUNKEN!"
- **getShips() / getShotAt()**: Let the game board see the current state of your side.

## Why do we use it?
It's the "referee" for your side of the board. Without it, you wouldn't know when you've lost or if your opponent's moves are legal.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. Placing a Ship (The "Referee")
```cpp
bool OwnGrid::placeShip(const Ship &ship) {
  if (!ship.isValid()) return false; // Proper ship Check

  // Check if we have that ship type left (e.g., Submarine)
  if (availableShips[ship.length()] <= 0) return false;

  // Check board boundaries and collisions
  for (const auto& gridPos : ship.occupiedArea()) {
     // ... checks if ship goes off the map ...
     // ... checks if gridPos is in an existing ship's blockedArea() ...
  }

  ships.push_back(ship); // Success! Add it.
  availableShips[ship.length()]--; // Use up one token
  return true;
}
```
- **The "Token" System**: It uses a `map` called `availableShips`. If you try to place 5 Submarines, the count hits 0 and the function will say "No!"

### 2. Taking a Hit
```cpp
Shot::Impact OwnGrid::takeBlow(const Shot &shot) {
  shotAt.insert(shot.getTargetPosition()); // Record the shot

  for (const auto& ship : ships) {
    if (ship.occupiedArea().count(shot.getTargetPosition()) > 0) {
      // It's a Hit! Now check if all segments are hit
      int hitsOnShip = 0;
      for (const auto& segment : ship.occupiedArea()) {
        if (shotAt.count(segment) > 0) hitsOnShip++;
      }
      if (hitsOnShip == ship.length()) return Shot::SUNKEN;
      return Shot::HIT;
    }
  }
  return Shot::NONE;
}
```
- **The Deduction**: Every time you get hit, the code looks at your ships one by one. If a missile lands on a square that a ship covers, it's a "HIT." If *every single square* of that ship has a missile on it, the code returns "SUNKEN."

---

# OpponentGrid Explanation

## What is this?
This is the **radar map** of the enemy territory. It's where you track your shots and try to solve the puzzle of where the enemy is hiding their ships.

## What is its job? (Duties)
1. **Track your progress**: It remembers every shot you've fired and if it was a "Hit" or a "Miss."
2. **"Connect the dots"**: This is its smartest duty! When you sink an enemy ship, this class scans the nearby hits to figure out exactly where the whole ship was (its bow and stern).
3. **Maintain a "Sunk" list**: It keeps a record of every enemy ship you've successfully destroyed.

## Inside the Code (Variables)
- `rows` and `columns` (int): The size of the enemy board (10x10).
- `shots` (map): A record of every target you fired at and the result (NONE, HIT, or SUNKEN).
- `sunkenShips` (vector): A list of enemy ships you've already found and destroyed.

## Tools it Uses (Member Functions)
- **shotResult(shot, impact)**: This is the main tool.
  1. It records your shot on the map.
  2. **The "Deduction" Logic**: If the impact is "SUNKEN," it automatically looks left-right and up-down to find the other connected hits. It then rebuilds the `Ship` object and moves it from "mystery hits" to the "sunken ships" list.
- **getShotsAt() / getSunkenShips()**: Returns the current state of your radar map.

## Why do we use it?
In Battleship, you can't see the enemy board. This class simulates the player's memory and their tactical map, turning random "X"s and "O"s back into concrete ships once they are destroyed.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. Recording Shots
```cpp
void OpponentGrid::shotResult(const Shot &shot, Shot::Impact impact) {
  shots[shot.getTargetPosition()] = impact; // Save the result on the map
  if (impact == Shot::SUNKEN) {
    // Advanced Deduction logic starts here...
  }
}
```

### 2. The Sunken Ship Sherlock Holmes logic
```cpp
if (impact == Shot::SUNKEN) {
  std::set<GridPosition> shipPositions;
  // 1. Look Left-Right and Up-Down from the final shot
  // 2. Add all nearby "HIT" markers to a list
  // 3. Find the lowest (Bow) and highest (Stern) points
  Ship sunkenShip(bow, stern);
  sunkenShips.push_back(sunkenShip);
}
```
- **How it works**: When the game says "Sunken!", the code doesn't actually know where the ship started or ended. It performs a search in all 4 directions from the last shot, finding all the "HIT" red-pegs connected to it. By finding the most extreme points (top-most/left-most vs bottom-most/right-most), it reconstructs the ship for your map!

---

# Board Explanation

## What is this?
The **Board** is the "Box" that holds the entire game. If this were a real board game, the Board would be the physical plastic case that unfolds to show both grids.

## What is its job? (Duties)
1. **Be a Container**: It holds one `OwnGrid` (your side) and one `OpponentGrid` (enemy side).
2. **Setup the game**: When you create a board, it handles creating both grids with the correct size (10x10).
3. **Provide access**: It gives other parts of the program (like the screen display) a way to look at the grids.

## Inside the Code (Variables)
- `ownGrid` (OwnGrid): The object representing your ships and incoming shots.
- `opponentGrid` (OpponentGrid): The object representing your shots at the enemy.

## Tools it Uses (Member Functions)
- **Board(rows, columns)**: The constructor. It sets up both sides of the game.
- **getRows() / getColumns()**: Tells the size of the whole board.
- **getOwnGrid() / getOpponentGrid()**: Returns a "link" or reference to the specific grid you want to interact with.

## Why do we use it?
It keeps the codes organized! Instead of passing around two different grids to every function, we just pass the one "Board" object that holds everything.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. The Constructor (Team Setup)
```cpp
Board::Board(int rows, int columns) 
    : ownGrid(rows, columns), opponentGrid(rows, columns) {}
```
- **Initialization List**: We use the special `:` syntax to initialize the two sub-grids (`ownGrid` and `opponentGrid`) as soon as the Board is born. This ensures they start with the correct size (10x10) right away.

### 2. Getters (Giving Access)
```cpp
OwnGrid& Board::getOwnGrid() { return ownGrid; }
```
- **References**: Notice the `&` symbol. This means the Board isn't sending back a *copy* of the grid, but a *direct link* to it. This allows other classes to actually place ships or record shots on the real board, not some fake duplicate.

---

# ConsoleView Explanation

## What is this?
This is the **TV screen** or the **Monitor** of the game. It takes all the invisible computer data (the lists of ships and shots) and turns it into a pretty picture that you can actually understand.

## What is its job? (Duties)
1. **Render the boards**: It prints two 10x10 grids side-by-side on your terminal screen.
2. **Use symbols**: It translates game logic into symbols:
   - `~` for Water (Water)
   - `#` for Ships (Ships)
   - `O` for Hits (Hits)
   - `^` for Misses (Misses)
3. **Align headers**: It prints column numbers (1-10) and row letters (A-J) so you can easily read the coordinates.

## Inside the Code (Variables)
- `board` (Board*): A "pointer" (a direct link) to the physical board that it needs to draw.

## Tools it Uses (Member Functions)
- **ConsoleView(board)**: Links the "TV" to the "Board Game."
- **print()**: The main engine. It loops through every row and column, decides what symbol belongs there (based on what the grids tell it), and prints it to the screen with neat spacing.

## Why do we use it?
Without this, the game would just be a bunch of silent data in the computer's memory. This is what makes the game "visible" and playable for a human!

---

# 🔎 Line-by-Line Code Walkthrough

### 1. Creating the Drawing Canvas
```cpp
std::vector<std::vector<char>> ownGridDisplay(rows);
for (int rowIdx = 0; rowIdx < rows; rowIdx++) {
    ownGridDisplay[rowIdx].resize(columns, '~');
}
```
- **What it does**: It creates a 2D "table" of characters in the computer's memory. Initially, it fills the entire thing with the `~` symbol (Water).

### 2. Layering the Map
The `print()` function works like a painter adding layers:
- **Layer 1: Ships**: It looks at all ships in `ownGrid.getShips()` and changes the `~` to `#` at their locations.
- **Layer 2: Shots**: It looks at `ownGrid.getShotAt()`.
  - If it hits a ship (`#`), it changes it to `O`.
  - If it hits water (`~`), it changes it to `^`.

### 3. Printing the Dual-Map
```cpp
for (int row = 0; row < rows; row++) {
    char rowLetter = 'A' + row;
    // ... Print one row of the left board ...
    // ... Print 2 spaces ...
    // ... Print one row of the right board ...
}
```
- **The Offset Trick**: By printing `'A' + row`, the code automatically turns row 0 into 'A', row 1 into 'B', and so on. This keeps the row letters perfectly aligned with the grid!

---

# main Explanation

## What is this?
The `main.cpp` file is the **Ignition Switch** of the program. When you tell the computer to "run," it always looks for `main()` first.

## What is its job? (Duties)
1. **Start the tests**: It doesn't actually play a game itself; instead, it calls several "test functions" to make sure the code is working perfectly.
2. **Organize execution**: it runs the tests for Part 1, Part 2, and Part 3 in order.
3. **Report progress**: It prints messages to the screen to tell you which part it is currently testing.

## Inside the Code (Variables)
- This file doesn't have many variables; it mostly just calls "Functions" (commands).

## Tools it Uses (Main Functions)
- **main()**: The entry point.
- **part1tests()**: Checks if basic Grid and Ship logic is correct.
- **part2tests()**: Checks if the Placement rules (Ships touching, fleet limits) work.
- **part3tests()**: Checks if Combat logic (Hitting, Sinking) is correct.
- **runFullGameTest()**: Runs a complete simulation of an entire game.

## Why do we use it?
Every C++ program *must* have a `main`. It's the conductor of the orchestra, telling everyone else when to start playing.

---

# 🔎 Line-by-Line Code Walkthrough

### 1. The Execution Loop
```cpp
int main() {
  std::cout << "=== Running Part 1 Tests ===" << std::endl;
  part1tests();
  // ... and so on ...
  return 0;
}
```
- **The Order**: `main` executes line-by-line. First, it prints a message, then it jumps into the code for `part1tests()`, waits for it to finish, and then moves to the next part.
- **`return 0`**: In C++, returning 0 at the end of `main` is the computer's way of saying "Everything finished successfully with zero errors."

### 2. External Functions
```cpp
void part1tests();
```
- **Declarations**: Notice this line at the top. It tells `main.cpp` that "There is a function called part1tests somewhere else in the project." This allows the program to link all the different files together into one big machine.

---

# part1tests Explanation

## What is this?
This is a **Quality Control (QC)** check for the most basic parts of the code.

## What is its job? (Duties)
It makes sure that `GridPosition` and `Ship` are doing their math correctly. It checks things like:
- Is "A1" a valid spot? (Yes)
- Is "A100" a valid spot? (No)
- If a ship is at A1 and A3, is its length 3? (Yes)

## Why do we use it?
If the foundations are broken, the whole house falls down. We use this to make sure the basic coordinates and ship sizes are 100% correct before building the rest of the game.

---

# part2tests Explanation

## What is this?
This is a **Rulebook Check**.

## What is its job? (Duties)
It focuses on the `OwnGrid` class to make sure it follows the ship placement rules:
- Can you place two ships touching each other? (The code should say No!)
- Can you place a ship off the edge of the map? (The code should say No!)
- Can you place 10 Carriers when you're only allowed 1? (The code should say No!)

## Why do we use it?
Battleship has strict rules. We use these tests to "try and cheat" so we can prove that the computer is smart enough to stop illegal moves.

---

# part3tests Explanation

## What is this?
This is a **Battlefield Simulation Check**.

## What is its job? (Duties)
It tests what happens when the game is actually in motion:
- If a ship sits on A1-A2, and you shoot A1, is it a "Hit"? (Yes)
- If you then shoot A2, is it "Sunken"? (Yes)
- Does the enemy's radar map correctly "solve" where your sunken ships were? (Yes)

## Why do we use it?
This ensures that the "scorekeeping" of the game is accurate. We want to make sure that when you hit a ship, the game actually notices!

---

# fullgametest Explanation

## What is this?
This is the **Grand Finale Test**. It's like a "dress rehearsal" for an entire game.

## What is its job? (Duties)
It simulates an ENTIRE match of Battleship. It does everything:
1. Places all 10 ships.
2. Fires dozens of shots.
3. Successfully sinks every single ship on the board.
4. Prints the boards at every step so you can see the progress.

## Why do we use it?
It's the ultimate proof that every single piece of the project (Grids, Ships, Console, Shots) works together in harmony. If this test passes, the whole project is ready for the professional world!
