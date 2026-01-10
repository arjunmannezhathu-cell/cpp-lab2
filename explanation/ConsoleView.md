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
