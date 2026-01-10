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
