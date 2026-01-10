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
