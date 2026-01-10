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
