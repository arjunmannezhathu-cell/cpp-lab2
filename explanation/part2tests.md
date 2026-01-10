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
