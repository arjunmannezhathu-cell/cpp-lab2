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
