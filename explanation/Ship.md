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
