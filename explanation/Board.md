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
