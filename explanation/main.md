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
